// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"

#include <Windows.ApplicationModel.Activation.h>

#include "DebugHelper.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "Helpers/GrantASCHelper.h"
#include "Kismet/KismetMathLibrary.h"

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

bool UARPGAbilitySystemComponent::TryActivateAbilityByTagActivationPolicy(const FGameplayTag AbilityTagToActivate,
                                                                          const FActivationPolicy ActivationPolicy)
{
	checkf(AbilityTagToActivate.IsValid(), TEXT("TAG Passed to %s is invalid"), *GetName())
	TArray<FGameplayAbilitySpec*> SpecPointers;

	if (ActivationPolicy == FActivationPolicy::All)
	{
		return TryActivateAbilitiesByTag(AbilityTagToActivate.GetSingleTagContainer());
	}

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), SpecPointers);

	if (!SpecPointers.IsEmpty())
	{
		return false;
	}

	checkf(SpecPointers[0], TEXT("Spec pointer is invalid %s"), *GetName());

	int Index = {0};

	switch (ActivationPolicy)
	{
	case FActivationPolicy::First:
		Index = 0;
		break;
	case FActivationPolicy::Last:
		Index = SpecPointers.Num() - 1;
		break;
	case FActivationPolicy::Random:
		Index = UKismetMathLibrary::RandomInteger(SpecPointers.Num());
		break;

	default:
		break;
	}

	return TryActivateAbility(SpecPointers[Index]->Handle, true);
}

bool UARPGAbilitySystemComponent::TryActivateAbilityByClassActivationPolicy(
	const TSubclassOf<UARPGGameplayAbility> AbilityToActivate,
	const FActivationPolicy ActivationPolicy)
{
	if (ActivationPolicy == FActivationPolicy::First)
	{
		return TryActivateAbilityByClass(AbilityToActivate);
	}

	const UGameplayAbility* const InAbilityCDO = AbilityToActivate.GetDefaultObject();
	TArray<int> Indexes = {};
	int Ite = 0;
	bool bAnyActivated = false;

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability != InAbilityCDO)
		{
			continue;
		}

		Indexes.Add(Ite);

		if (ActivationPolicy == FActivationPolicy::All)
		{
			bAnyActivated |= TryActivateAbility(Spec.Handle, true);
		}
		Ite++;
	}

	if (ActivationPolicy == FActivationPolicy::All)
	{
		return bAnyActivated;
	}

	int Index = {0};

	switch (ActivationPolicy)
	{
	case FActivationPolicy::Last:
		Index = Indexes.Num() - 1;
		break;
	case FActivationPolicy::Random:
		Index = UKismetMathLibrary::RandomInteger(Indexes.Num());
		break;
	default:
		break;
	}

	bAnyActivated = TryActivateAbility(GetActivatableAbilities()[Index].Handle, true);

	return bAnyActivated;
}
