// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGEnemyGameplayAbility.h"
#include "GameplayAbility_SpawnAdds.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ARPG_API UGameplayAbility_SpawnAdds : public UARPGEnemyGameplayAbility
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta=(AllowPrivateAccess))
	TSoftClassPtr<AARPGEnemyCharacter> EnemyToSpawn{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta=(AllowPrivateAccess))
	int HowManyToSpawn{3};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta=(AllowPrivateAccess))
	float SpawnDistance{200};

public:
	UGameplayAbility_SpawnAdds();

	UFUNCTION()
	void OnActorSpawned(TArray<AActor*> Actors);
	UFUNCTION()
	void OnActorNotSpawned(TArray<AActor*> Actors);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
};
