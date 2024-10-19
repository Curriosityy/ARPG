// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UHeroGameplayAbility_TargetLock : public UARPGHeroGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float TraceDepth{};
	UPROPERTY(EditDefaultsOnly)
	FVector BoxHalfSize{};
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannels = {};
	UPROPERTY(EditDefaultsOnly)
	bool bShowDebug{false};
	UPROPERTY(EditDefaultsOnly)
	float Precision{.05f};

public:
	UHeroGameplayAbility_TargetLock();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

private:
	void GetValidLockActor(TArray<FHitResult>& Results);
	AActor* GetBestLockActor(const TArray<FHitResult>& Results);
};
