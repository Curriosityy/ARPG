// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameplayAbilitySpecHandle.h"
#include "Types/ARPGStructTypes.h"

class UGameplayEffect;
class UARPGEnemyGameplayAbility;
class UARPGAbilitySystemComponent;
class UARPGGameplayAbility;
/**
 * 
 */
namespace GrantASCHelper
{
	class GrantASCHelper
	{
	public:
		static void GrantAbility(const TSubclassOf<UARPGGameplayAbility>& Ability,
		                         UARPGAbilitySystemComponent* InASC, const int32 Level,
		                         FGameplayAbilitySpecHandle& AbilitySpecHandle);


		static void GrantHeroAbility(const FARPGHeroAbilitySet& ToGrant,
		                             UARPGAbilitySystemComponent* InAsc, int32 Level,
		                             FGameplayAbilitySpecHandle& AbilitySpecHandle);

		static void GrantHeroAbilities(const TArray<FARPGHeroAbilitySet>& AbilitiesToGrant,
		                               UARPGAbilitySystemComponent* InAsc, const int32 Level,
		                               TArray<FGameplayAbilitySpecHandle>& AbilitiesSpecHandle);


		static void GrantAbilities(const TArray<TSubclassOf<UARPGGameplayAbility>>& AbilitiesToGrant,
		                           UARPGAbilitySystemComponent* InASC, const int32 Level,
		                           TArray<FGameplayAbilitySpecHandle>& AbilitiesSpecHandle);

		static void GrantEnemyAbilities(
			const TArray<TSubclassOf<UARPGEnemyGameplayAbility>>& AbilitiesToGrant, UARPGAbilitySystemComponent* InASC,
			const int32 Level, TArray<FGameplayAbilitySpecHandle>& AbilitiesSpecHandle);

		static void GrantGameplayEffectsToSelf(
			const TArray<TSubclassOf<UGameplayEffect>>& EffectsToGrant, UARPGAbilitySystemComponent* InASC,
			const int32 Level);
		static void GrantGameplayEffectToSelf(
			const TSubclassOf<UGameplayEffect>& EffectsToGrant, UARPGAbilitySystemComponent* InASC,
			const int32 Level);
	};
}
