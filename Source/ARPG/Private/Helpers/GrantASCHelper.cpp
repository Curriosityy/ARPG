// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/GrantASCHelper.h"

#include "DebugHelper.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGEnemyGameplayAbility.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "AbilitySystem/Abilities/ARPGHeroGameplayAbility.h"

void GrantASCHelper::GrantASCHelper::GrantAbility(const TSubclassOf<UARPGGameplayAbility>& Ability,
                                                  UARPGAbilitySystemComponent* InASC, const int32 Level,
                                                  FGameplayAbilitySpecHandle& AbilitySpecHandle)
{
	checkf(Ability, TEXT("UDataAsset_StartUpDataBase::GrantAbility : ability is NULL"));
	checkf(InASC, TEXT("UDataAsset_StartUpDataBase::GrantAbility: InASC is NULL"));

	FGameplayAbilitySpec Spec{Ability};
	Spec.SourceObject = InASC->GetAvatarActor();
	Spec.Level = Level;

	AbilitySpecHandle = InASC->GiveAbility(Spec);
}

void GrantASCHelper::GrantASCHelper::GrantHeroAbility(const FARPGHeroAbilitySet& ToGrant,
                                                      UARPGAbilitySystemComponent* InAsc, int32 Level,
                                                      FGameplayAbilitySpecHandle& AbilitySpecHandle)
{
	FGameplayAbilitySpec AbilitySpec{ToGrant.AbilityToGrant};
	AbilitySpec.SourceObject = InAsc->GetAvatarActor();
	AbilitySpec.Level = Level;
	AbilitySpec.DynamicAbilityTags.AddTag(ToGrant.InputTag);
	AbilitySpecHandle = InAsc->GiveAbility(AbilitySpec);
}

void GrantASCHelper::GrantASCHelper::GrantHeroAbilities(const TArray<FARPGHeroAbilitySet>& AbilitiesToGrant,
                                                        UARPGAbilitySystemComponent* InAsc, const int32 Level,
                                                        TArray<FGameplayAbilitySpecHandle>& AbilitiesSpecHandle)
{
	FGameplayAbilitySpecHandle SpecHandle;
	for (const FARPGHeroAbilitySet& ToGrant : AbilitiesToGrant)
	{
		if (!ToGrant.IsValid())
		{
			continue;
		}
		GrantHeroAbility(ToGrant, InAsc, Level, SpecHandle);
		AbilitiesSpecHandle.Add(SpecHandle);
	}
}

void GrantASCHelper::GrantASCHelper::GrantAbilities(
	const TArray<TSubclassOf<UARPGGameplayAbility>>& AbilitiesToGrant, UARPGAbilitySystemComponent* InASC,
	const int32 Level, TArray<FGameplayAbilitySpecHandle>& AbilitiesSpecHandle)
{
	FGameplayAbilitySpecHandle SpecHandle;
	for (const TSubclassOf<UARPGGameplayAbility>& ToGrant : AbilitiesToGrant)
	{
		GrantAbility(ToGrant, InASC, Level, SpecHandle);
		AbilitiesSpecHandle.Add(SpecHandle);
	}
}

void GrantASCHelper::GrantASCHelper::GrantEnemyAbilities(
	const TArray<TSubclassOf<UARPGEnemyGameplayAbility>>& AbilitiesToGrant, UARPGAbilitySystemComponent* InASC,
	const int32 Level, TArray<FGameplayAbilitySpecHandle>& AbilitiesSpecHandle)
{
	FGameplayAbilitySpecHandle SpecHandle;
	for (const TSubclassOf<UARPGEnemyGameplayAbility>& ToGrant : AbilitiesToGrant)
	{
		GrantAbility(ToGrant, InASC, Level, SpecHandle);
		AbilitiesSpecHandle.Add(SpecHandle);
	}
}

void GrantASCHelper::GrantASCHelper::GrantGameplayEffectsToSelf(
	const TArray<TSubclassOf<UGameplayEffect>>& EffectsToGrant, UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	for (const TSubclassOf<UGameplayEffect>& ToGrant : EffectsToGrant)
	{
		if (!ToGrant)
		{
			continue;
		}

		GrantGameplayEffectToSelf(ToGrant, InASC, Level);
	}
}

void GrantASCHelper::GrantASCHelper::GrantGameplayEffectToSelf(
	const TSubclassOf<UGameplayEffect>& EffectsToGrant, UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	InASC->ApplyGameplayEffectToSelf(EffectsToGrant->GetDefaultObject<UGameplayEffect>(),
	                                 1,
	                                 InASC->MakeEffectContext());
}
