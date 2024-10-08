// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"

#include <Windows.ApplicationModel.Activation.h>

#include "DebugHelper.h"
#include "Helpers/GrantAbilityHelper.h"

int32 UARPGAbilitySystemComponent::GetActivatableAbilityIndexBasedOnDynamicTag(
	const FGameplayTag& InInputTag)
{
	return GetActivatableAbilities().IndexOfByPredicate([&]
	(const FGameplayAbilitySpec& Ability)
		{
			return Ability.DynamicAbilityTags.HasTagExact(InInputTag);
		});
}

void UARPGAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	int idx = GetActivatableAbilityIndexBasedOnDynamicTag(InInputTag);

	if (INDEX_NONE == idx)
	{
		return;
	}

	TryActivateAbility(GetActivatableAbilities()[idx].Handle);
}

void UARPGAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	int idx = GetActivatableAbilityIndexBasedOnDynamicTag(InInputTag);

	if (INDEX_NONE == idx)
	{
	}

	//(Ability.Handle);
}

void UARPGAbilitySystemComponent::GrandHeroWeaponAbilities(const TArray<FARPGHeroAbilitySet> HeroAbilitiesesToGrant,
                                                           int32 ApplyLevel)
{
	Debug::Print("GrandHeroWeaponAbilities");
	GrantAbilityHelper::GrantAbilityHelper::GrantHeroAbilities(HeroAbilitiesesToGrant, this, ApplyLevel);
}
