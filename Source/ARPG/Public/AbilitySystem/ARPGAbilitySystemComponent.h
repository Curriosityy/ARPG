// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGAbilitySystemComponent.generated.h"

/**
 * 
 */
UENUM()
enum class FActivationPolicy
{
	First,
	Last,
	Random,
	All
};

UCLASS()
class ARPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	int32 GetActivatableAbilityIndexBasedOnDynamicTag(const FGameplayTag& InInputTag);
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability", meta = (ApplyLevel = "1"))
	void GrandHeroWeaponAbilities(const TArray<FARPGHeroAbilitySet> HeroAbilitiesesToGrant, int32 ApplyLevel,
	                              TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& AbilitiesToRemove);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability|TryActivate")
	bool TryActivateAbilityByTagActivationPolicy(FGameplayTag AbilityTagToActivate, FActivationPolicy ActivationPolicy);
	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability|TryActivate")
	bool TryActivateAbilityByClassActivationPolicy(TSubclassOf<UARPGGameplayAbility> AbilityToActivate,
	                                               FActivationPolicy ActivationPolicy);
};
