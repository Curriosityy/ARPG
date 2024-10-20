// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "InteractiveGizmo.h"
#include "AbilitySystem/Tasks/AbilityTask_ExecuteOnTick.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Camera/CameraComponent.h"
#include "Characters/ARPGHeroCharacter.h"
#include "Components/SizeBox.h"
#include "Controllers/ARPGHeroController.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "Interfaces/OverHeadDebuggerInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UHeroGameplayAbility_TargetLock::UHeroGameplayAbility_TargetLock()
{
	AbilityTags.AddTag(ARPGGameplayTags::Player_Ability_TargetLock);

	ActivationOwnedTags.AddTag(ARPGGameplayTags::Player_Status_TargetLocking);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//bRetriggerInstancedAbility = true;
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
	                                                             RotationSpeed);

	OwningActor->SetActorRotation({0, InterpRotator.Yaw, 0});

	GetHeroControllerFromActorInfo()->SetControlRotation({InterpRotator.Pitch, InterpRotator.Yaw, 0});
}

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo,
                                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Setup();


	LockOnNewTarget();

	if (!CurrentLockedTarget.IsValid())
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	Task = UAbilityTask_ExecuteOnTick::ExecuteOnTick(this);
	Task->OnTick.AddDynamic(this, &ThisClass::OnTick);
	Task->ReadyForActivation();

	CommitAbility(Handle, ActorInfo, ActivationInfo);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	TargetLockingImage->SetVisibility(ESlateVisibility::Hidden);
}
