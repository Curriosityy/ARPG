// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/GrantAbilityHelper.h"

#include "DebugHelper.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

void GrantAbilityHelper::GrantAbilityHelper::GrantAbility(const TSubclassOf<UARPGGameplayAbility>& Ability,
                                                          UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	checkf(Ability, TEXT("UDataAsset_StartUpDataBase::GrantAbility : ability is NULL"));
	checkf(InASC, TEXT("UDataAsset_StartUpDataBase::GrantAbility: InASC is NULL"));

	FGameplayAbilitySpec Spec{Ability};
	Spec.SourceObject = InASC->GetAvatarActor();
	Spec.Level = Level;

	InASC->GiveAbility(Spec);
}

void GrantAbilityHelper::GrantAbilityHelper::GrantHeroAbility(const FARPGHeroAbilitySet& ToGrant,
                                                              UARPGAbilitySystemComponent* InAsc, int32 Level)
{
	FGameplayAbilitySpec AbilitySpec{ToGrant.AbilityToGrant};
	AbilitySpec.SourceObject = InAsc->GetAvatarActor();
	AbilitySpec.Level = Level;
	AbilitySpec.DynamicAbilityTags.AddTag(ToGrant.InputTag);
	Debug::Print(
		FString::Printf(TEXT("GrantAbilityHelper::GrantHeroAbility %s"), *AbilitySpec.DynamicAbilityTags.ToString()));
	InAsc->GiveAbility(AbilitySpec);
}

void GrantAbilityHelper::GrantAbilityHelper::GrantHeroAbilities(const TArray<FARPGHeroAbilitySet>& AbilitiesToGrant,
                                                                UARPGAbilitySystemComponent* InAsc, const int32 Level)
{
	for (const FARPGHeroAbilitySet& ToGrant : AbilitiesToGrant)
	{
		if (!ToGrant.IsValid())
		{
			continue;
		}
		GrantHeroAbility(ToGrant, InAsc, Level);
	}
}

void GrantAbilityHelper::GrantAbilityHelper::GrantAbilities(
	const TArray<TSubclassOf<UARPGGameplayAbility>>& AbilitiesToGrant, UARPGAbilitySystemComponent* InASC,
	const int32 Level)
{
	for (const TSubclassOf<UARPGGameplayAbility>& ToGrant : AbilitiesToGrant)
	{
		GrantAbility(ToGrant, InASC, Level);
	}
}
