// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ARPGGameplayAbility.generated.h"

class UPawnCombatComponent;

UENUM()
enum class EARPGAbilityActivationPolicy : uint8
{
	OnTrigger,
	OnGiven,
};

/**
 * 
 */
UCLASS()
class ARPG_API UARPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="ARPG Ability")
	EARPGAbilityActivationPolicy Policy = EARPGAbilityActivationPolicy::OnTrigger;

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
	                        const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo,
	                        bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	UPawnCombatComponent* GetCombatComponentFromActorInfo() const;
};
