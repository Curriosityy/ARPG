// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "AbilitySystemComponent.h"
#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "InteractiveGizmo.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_ExecuteOnTick.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Camera/CameraComponent.h"
#include "Characters/ARPGHeroCharacter.h"
#include "Components/SizeBox.h"
#include "Controllers/ARPGHeroController.h"
#include "DTO/InputActionValueDTO.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Interfaces/OverHeadDebuggerInterface.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UHeroGameplayAbility_TargetLock::UHeroGameplayAbility_TargetLock()
{
	AbilityTags.AddTag(ARPGGameplayTags::Player_Ability_TargetLock);

	ActivationOwnedTags.AddTag(ARPGGameplayTags::Player_Status_TargetLocking);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//bRetriggerInstancedAbility = true;
}

bool UHeroGameplayAbility_TargetLock::TryLockOnNewTarget(const FGameplayAbilitySpecHandle& Handle,
                                                         const FGameplayAbilityActorInfo* ActorInfo,
                                                         const FGameplayAbilityActivationInfo&
                                                         ActivationInfo)
{
	Setup();

	LockOnNewTarget();

	if (!CurrentLockedTarget.IsValid())
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return false;
	}

	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->bOrientRotationToMovement = false;
	GetHeroCharacterFromActorInfo()->Controller->SetIgnoreLookInput(true);

	return true;
}

void UHeroGameplayAbility_TargetLock::TryChangeLockedTarget(FGameplayEventData Payload)
{
	check(Payload.OptionalObject);
	const UInputActionValueDTO* DTO = Cast<UInputActionValueDTO>(Payload.OptionalObject);
	const FVector2D Value = DTO->Value.Get<FVector2D>();
	TArray<FHitResult> TargetActors;
	GetValidLockActor(TargetActors);

	TargetActors = TargetActors.FilterByPredicate([&](const FHitResult& Result)
	{
		return Result.GetActor() != CurrentLockedTarget;
	});

	const FVector ActorPosition = GetAvatarActorFromActorInfo()->GetActorLocation();

	if (Value.X < 0)
	{
		//FindTargetOnLeft
		TargetActors = TargetActors.FilterByPredicate([&](const FHitResult& Result)
		{
			return GetAvatarActorFromActorInfo()->
			       GetActorForwardVector().
			       Cross(Result.ImpactPoint - ActorPosition).Z < 0;
		});
	}

	if (Value.X > 0)
	{
		//FindTargetOnRight
		TargetActors = TargetActors.FilterByPredicate([&](const FHitResult& Result)
		{
			return GetAvatarActorFromActorInfo()->
			       GetActorForwardVector().
			       Cross((Result.ImpactPoint - ActorPosition).GetSafeNormal()).Z > 0;
		});
	}

	for (const FHitResult& Result : TargetActors)
	{
		if (IOverHeadDebuggerInterface* Interface = Cast<IOverHeadDebuggerInterface>(Result.GetActor()))
		{
			Interface->SetOverHeadDebugText((GetAvatarActorFromActorInfo()->
			                                 GetActorForwardVector().
			                                 Cross((Result.ImpactPoint - ActorPosition).GetSafeNormal()).
			                                 ToString()));
		}
	}

	AActor* BestActor = nullptr;
	float BestProduct = 12;

	for (const FHitResult& Result : TargetActors)
	{
		const float CrossProduct = GetAvatarActorFromActorInfo()->
		                           GetActorForwardVector().
		                           Cross((Result.ImpactPoint - ActorPosition).GetSafeNormal()).Z;

		if (abs(CrossProduct) < BestProduct)
		{
			BestActor = Result.GetActor();
			BestProduct = abs(CrossProduct);
		}
	}

	if (BestActor)
	{
		Debug::Print("BestActor: " + FString(BestActor->GetName()) + "\n");
		Debug::Print("CurrentLockedTarget: " + FString(CurrentLockedTarget->GetName()) + "\n");
		CurrentLockedTarget = BestActor;
	}
}

void UHeroGameplayAbility_TargetLock::OnTick(float DeltaTime)
{
	if (!CurrentLockedTarget.IsValid())
	{
		LockOnNewTarget();
	}

	if (!CurrentLockedTarget.IsValid())
	{
		EndAbility(
			GetCurrentAbilitySpecHandle(),
			CurrentActorInfo,
			GetCurrentActivationInfo(),
			true,
			false);

		return;
	}

	SetWidgetPositionOnValidTarget();

	if (!UARPGFunctionLibrary::NativeDoesActorHaveTag(GetOwningActorFromActorInfo(),
	                                                  ARPGGameplayTags::Player_Status_Rolling))
	{
		SetRotationOnValidTarget(DeltaTime);
	}

	if (UARPGFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedTarget.Get(), ARPGGameplayTags::Shared_Status_Death))
	{
		CurrentLockedTarget = {};
	}
}

void UHeroGameplayAbility_TargetLock::GetValidLockActor(TArray<FHitResult>& Results)
{
	const AARPGHeroCharacter* OwningActor = GetHeroCharacterFromActorInfo();
	const FVector ForwardVector = OwningActor->GetFollowCamera()->GetForwardVector();

	UKismetSystemLibrary::BoxTraceMultiForObjects(OwningActor,
	                                              OwningActor->GetActorLocation(),
	                                              OwningActor->GetActorLocation() + ForwardVector
	                                              * TraceDepth,
	                                              BoxHalfSize,
	                                              ForwardVector.ToOrientationRotator(),
	                                              TraceChannels,
	                                              false,
	                                              {},
	                                              bShowDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
	                                              Results,
	                                              true);
	//Filters
	Results = Results.FilterByPredicate([](const FHitResult& Result)
	{
		return Cast<IAbilitySystemInterface>(Result.GetActor());
	});

	Results = Results.FilterByPredicate([](const FHitResult& Result)
	{
		return !UARPGFunctionLibrary::NativeDoesActorHaveTag(Result.GetActor(), ARPGGameplayTags::Shared_Status_Death);
	});
}


AActor* UHeroGameplayAbility_TargetLock::GetBestLockActor(const TArray<FHitResult>& Results)
{
	const AARPGHeroCharacter* OwningActor = GetHeroCharacterFromActorInfo();
	const FVector ForwardVector = OwningActor->GetFollowCamera()->GetForwardVector();

	AActor* BestActor{};
	double BestNormal{-1};
	double BestDistance{-1};

	for (const FHitResult& Result : Results)
	{
		const double Normal = UKismetMathLibrary::Dot_VectorVector(ForwardVector,
		                                                           (Result.ImpactPoint - OwningActor->
			                                                           GetActorLocation()).
		                                                           GetSafeNormal());

		if (IOverHeadDebuggerInterface* Interface = Cast<IOverHeadDebuggerInterface>(Result.GetActor()))
		{
			Interface->SetOverHeadDebugText(FString::SanitizeFloat(Normal));
		}

		if (Normal < BestNormal)
		{
			continue;
		}

		//Super close normal variant
		//Pick enemy based on distance
		if (Normal - Precision < BestNormal &&
			BestDistance < Result.Distance)
		{
			continue;
		}


		BestActor = Result.GetActor();
		BestNormal = Normal;
		BestDistance = Result.Distance;
	}

	return BestActor;
}

void UHeroGameplayAbility_TargetLock::Setup()
{
	if (!TargetLockingImage)
	{
		checkf(TargetLockingImageClass, TEXT("TargetLockingImageClass is not setted"))
		TargetLockingImage = CreateWidget<UUserWidget>(GetHeroControllerFromActorInfo(), TargetLockingImageClass);
		check(TargetLockingImage)
		TargetLockingImage->SetVisibility(ESlateVisibility::Hidden);
		TargetLockingImage->AddToViewport(-1);
	}

	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)->AddMappingContext(InputMapping, 3);
}

void UHeroGameplayAbility_TargetLock::SetWidgetPositionOnValidTarget()
{
	check(CurrentLockedTarget.IsValid());
	check(TargetLockingImage);

	FVector2D OutScreenPosition{};
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetHeroControllerFromActorInfo(),
	                                                           CurrentLockedTarget->GetActorLocation(),
	                                                           OutScreenPosition,
	                                                           true);


	FVector2d ImageSize = TargetLockingImage->GetDesiredSize();

	if (ImageSize == FVector2D::ZeroVector)
	{
		//Creation tick return 00
		TargetLockingImage->WidgetTree->ForEachWidget([&](UWidget* Widget)
		{
			if (const USizeBox* SizeBox = Cast<USizeBox>(Widget))
			{
				ImageSize.X = SizeBox->GetWidthOverride();
				ImageSize.Y = SizeBox->GetHeightOverride();
			}
		});
	}

	TargetLockingImage->SetPositionInViewport(OutScreenPosition - ImageSize / 2, false);
}

void UHeroGameplayAbility_TargetLock::SetTarget(AActor* BestTarget)
{
	check(BestTarget)
	CurrentLockedTarget = {BestTarget};
	SetWidgetPositionOnValidTarget();
	TargetLockingImage->SetVisibility(ESlateVisibility::Visible);
}

void UHeroGameplayAbility_TargetLock::LockOnNewTarget()
{
	TArray<FHitResult> Results;
	GetValidLockActor(Results);

	if (Results.Num() <= 0)
	{
		return;
	}

	AActor* BestTarget = GetBestLockActor(Results);

	if (bShowDebug)
	{
		UKismetSystemLibrary::DrawDebugLine(BestTarget, GetAvatarActorFromActorInfo()->GetActorLocation(),
		                                    BestTarget->GetActorLocation(), FColor::Blue, 6, 2);
	}

	SetTarget(BestTarget);
}

void UHeroGameplayAbility_TargetLock::SetRotationOnValidTarget(float DeltaTime)
{
	check(CurrentLockedTarget.IsValid());
	AActor* OwningActor = GetAvatarActorFromActorInfo();
	const FRotator CurrentRotation = GetHeroControllerFromActorInfo()->GetControlRotation();
	const FRotator FinalRotation = UKismetMathLibrary::FindLookAtRotation(
		OwningActor->GetActorLocation(),
		CurrentLockedTarget->GetActorLocation());


	const FRotator InterpRotator = UKismetMathLibrary::RInterpTo(CurrentRotation,
	                                                             FinalRotation,
	                                                             DeltaTime,
	                                                             CameraRotationSpeed);

	const FRotator HeroInterpRotator = UKismetMathLibrary::RInterpTo(OwningActor->GetActorRotation(),
	                                                                 FinalRotation,
	                                                                 DeltaTime,
	                                                                 CameraRotationSpeed);


	OwningActor->SetActorRotation({0, HeroInterpRotator.Yaw, 0});

	GetHeroControllerFromActorInfo()->SetControlRotation({InterpRotator.Pitch, InterpRotator.Yaw, 0});
}

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo,
                                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!TryLockOnNewTarget(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	TickTask = UAbilityTask_ExecuteOnTick::ExecuteOnTick(this);
	TickTask->OnTick.AddDynamic(this, &ThisClass::OnTick);
	TickTask->ReadyForActivation();
	EffectHandle = ApplyGameplayEffectSpecToOwner(
		Handle,
		ActorInfo,
		ActivationInfo,
		MakeOutgoingGameplayEffectSpec(TargetLockingGameplayEffect));

	WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,
	                                                                  ARPGGameplayTags::Player_Event_ChangeTarget);
	WaitEventTask->EventReceived.AddDynamic(this, &ThisClass::TryChangeLockedTarget);
	WaitEventTask->ReadyForActivation();
	CommitAbility(Handle, ActorInfo, ActivationInfo);
}


//TODO REFACTOR
void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (auto* Movement = GetHeroCharacterFromActorInfo()->GetCharacterMovement())
	{
		Movement->bOrientRotationToMovement = true;
	}

	if (AController* Controller = GetHeroCharacterFromActorInfo()->Controller)
	{
		Controller->SetIgnoreLookInput(false);
	}


	if (GetHeroControllerFromActorInfo())
	{
		const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();

		if (UEnhancedInputLocalPlayerSubsystem* const InputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			InputSubsystem->RemoveMappingContext(InputMapping);
		}
	}


	TargetLockingImage->SetVisibility(ESlateVisibility::Hidden);
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(EffectHandle);
}
