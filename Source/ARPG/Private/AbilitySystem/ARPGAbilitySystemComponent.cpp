// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"

#include <Windows.ApplicationModel.Activation.h>

#include "DebugHelper.h"
#include "Helpers/GrantASCHelper.h"

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
                                                           int32 ApplyLevel,
                                                           TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles)
{
	GrantASCHelper::GrantASCHelper::GrantHeroAbilities(HeroAbilitiesesToGrant, this, ApplyLevel,
	                                                   AbilitySpecHandles);
}

void UARPGAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& AbilitiesToRemove)
{
	for (const FGameplayAbilitySpecHandle& ToRemove : AbilitiesToRemove)
	{
		if (!ToRemove.IsValid())
		{
		}

		ClearAbility(ToRemove);
	}

	AbilitiesToRemove.Empty();
}

bool UARPGAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	checkf(AbilityTagToActivate.IsValid(), TEXT("TAG Passed to %s is invalid"), *GetName())
	TArray<FGameplayAbilitySpec*> SpecPointers;

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), SpecPointers);

	if (!SpecPointers.IsEmpty())
	{
		return false;
	}
	checkf(SpecPointers[0], TEXT("Spec pointer is invalid %s"), *GetName());

	return TryActivateAbility(SpecPointers[0]->Handle, true);
}
