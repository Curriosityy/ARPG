// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/GrantAbilityHelper.h"

#include "DebugHelper.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

void GrantAbilityHelper::GrantAbilityHelper::GrantAbility(const TSubclassOf<UARPGGameplayAbility>& Ability,
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

void GrantAbilityHelper::GrantAbilityHelper::GrantHeroAbility(const FARPGHeroAbilitySet& ToGrant,
                                                              UARPGAbilitySystemComponent* InAsc, int32 Level,
                                                              FGameplayAbilitySpecHandle& AbilitySpecHandle)
{
	FGameplayAbilitySpec AbilitySpec{ToGrant.AbilityToGrant};
	AbilitySpec.SourceObject = InAsc->GetAvatarActor();
	AbilitySpec.Level = Level;
	AbilitySpec.DynamicAbilityTags.AddTag(ToGrant.InputTag);
	AbilitySpecHandle = InAsc->GiveAbility(AbilitySpec);
}

void GrantAbilityHelper::GrantAbilityHelper::GrantHeroAbilities(const TArray<FARPGHeroAbilitySet>& AbilitiesToGrant,
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

void GrantAbilityHelper::GrantAbilityHelper::GrantAbilities(
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
