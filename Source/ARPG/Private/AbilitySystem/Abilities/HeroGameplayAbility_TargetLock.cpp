// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "InteractiveGizmo.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Camera/CameraComponent.h"
#include "Characters/ARPGHeroCharacter.h"
#include "Components/SizeBox.h"
#include "Controllers/ARPGHeroController.h"
#include "Interfaces/OverHeadDebuggerInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UHeroGameplayAbility_TargetLock::UHeroGameplayAbility_TargetLock()
{
	AbilityTags.AddTag(ARPGGameplayTags::Player_Ability_TargetLock);

	ActivationOwnedTags.AddTag(ARPGGameplayTags::Player_Status_TargetLock);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//bRetriggerInstancedAbility = true;
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


		if ((Normal - Precision) > BestNormal)
		{
			BestActor = Result.GetActor();
			BestNormal = Normal;
			BestDistance = Result.Distance;
			continue;
		}

		//Super close normal variant
		//Pick enemy based on distance
		if (BestDistance < Result.Distance)
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

void UHeroGameplayAbility_TargetLock::SetTarget(AActor* BestTarget)
{
	check(BestTarget)
	CurrentLockedActor = {BestTarget};
	FVector2D OutScreenPosition{};
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetHeroControllerFromActorInfo(),
	                                                           CurrentLockedActor->GetActorLocation(),
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
	TargetLockingImage->SetVisibility(ESlateVisibility::Visible);
}

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo,
                                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Setup();

	TArray<FHitResult> Results;
	GetValidLockActor(Results);

	if (Results.Num() <= 0)
	{
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	AActor* BestTarget = GetBestLockActor(Results);

	UKismetSystemLibrary::DrawDebugLine(BestTarget, GetAvatarActorFromActorInfo()->GetActorLocation(),
	                                    BestTarget->GetActorLocation(), FColor::Blue, 6, 2);

	SetTarget(BestTarget);

	CommitAbility(Handle, ActorInfo, ActivationInfo);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
