// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	int32 GetActivatableAbilityIndexBasedOnDynamicTag(const FGameplayTag& InInputTag);
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Warriot|Ability", meta = (ApplyLevel = "1"))
	void GrandHeroWeaponAbilities(const TArray<FARPGHeroAbilitySet> HeroAbilitiesesToGrant, int32 ApplyLevel);
};
