// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Types/ARPGStructTypes.h"

class UARPGAbilitySystemComponent;
class UARPGGameplayAbility;
/**
 * 
 */
namespace GrantAbilityHelper
{
	class GrantAbilityHelper
	{
	public:
		static void GrantAbility(const TSubclassOf<UARPGGameplayAbility>& Ability,
		                         UARPGAbilitySystemComponent* InASC, const int32 Level);


		static void GrantHeroAbility(const FARPGHeroAbilitySet& ToGrant,
		                             UARPGAbilitySystemComponent* InAsc, int32 Level);

		static void GrantHeroAbilities(const TArray<FARPGHeroAbilitySet>& AbilitiesToGrant,
		                               UARPGAbilitySystemComponent* InAsc, const int32 Level);


		static void GrantAbilities(const TArray<TSubclassOf<UARPGGameplayAbility>>& AbilitiesToGrant,
		                           UARPGAbilitySystemComponent* InASC, const int32 Level);
	};
}