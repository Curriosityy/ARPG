// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"

#include <Windows.ApplicationModel.Activation.h>

const FGameplayAbilitySpec& UARPGAbilitySystemComponent::GetAbilitySpecBasedOnDynamicTag(const FGameplayTag& InInputTag)
{
	FGameplayAbilitySpec AbilitySpec;

	for (const FGameplayAbilitySpec& ActivatableAbility : GetActivatableAbilities())
	{
		if (!ActivatableAbility.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			continue;
		}

		return ActivatableAbility;
	}

	return AbilitySpec;
}

void UARPGAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	const FGameplayAbilitySpec& Ability = GetAbilitySpecBasedOnDynamicTag(InInputTag);

	if (!Ability.Handle.IsValid())
	{
		return;
	}

	TryActivateAbility(Ability.Handle);
}

void UARPGAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	const FGameplayAbilitySpec& Ability = GetAbilitySpecBasedOnDynamicTag(InInputTag);

	if (!Ability.Handle.IsValid())
	{
	}

	//(Ability.Handle);
}
