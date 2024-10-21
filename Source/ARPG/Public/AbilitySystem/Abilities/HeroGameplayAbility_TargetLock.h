// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Abilities/ARPGHeroGameplayAbility.h"
#include "AbilitySystem/Tasks/AbilityTask_ExecuteOnTick.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class UInputMappingContext;
class UUserWidget;
/**
 * 
 */
UCLASS(Abstract)
class ARPG_API UHeroGameplayAbility_TargetLock : public UARPGHeroGameplayAbility
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float TraceDepth{};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	FVector BoxHalfSize{};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannels{};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	bool bShowDebug{false};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float Precision{.05f};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float CameraRotationSpeed{5};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float HeroRotationSpeed{5};
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<UUserWidget> TargetLockingImageClass{};

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<UGameplayEffect> TargetLockingGameplayEffect{};

	UPROPERTY()
	TObjectPtr<UUserWidget> TargetLockingImage;
	UPROPERTY()
	TWeakObjectPtr<AActor> CurrentLockedTarget;

	UPROPERTY()
	TObjectPtr<UAbilityTask_ExecuteOnTick> TickTask;

	UPROPERTY()
	FActiveGameplayEffectHandle TickEffectHandle;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitGameplayEvent> WaitEventTask;

	UPROPERTY()
	FActiveGameplayEffectHandle EffectHandle;

public:
	UHeroGameplayAbility_TargetLock();

	bool TryLockOnNewTarget(const FGameplayAbilitySpecHandle& Handle,
	                        const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo& ActivationInfo);

	UFUNCTION()
	void TryChangeLockedTarget(FGameplayEventData Payload);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

private:
	void GetValidLockActor(TArray<FHitResult>& Results);
	AActor* GetBestLockActor(const TArray<FHitResult>& Results);
	void Setup();
	void SetWidgetPositionOnValidTarget();
	void SetTarget(AActor* BestTarget);
	void LockOnNewTarget();
	void SetRotationOnValidTarget(float DeltaTime);
	UFUNCTION()
	void OnTick(float DeltaTime);
};
