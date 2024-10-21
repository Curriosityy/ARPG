// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"

#include <Windows.ApplicationModel.Activation.h>

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "GlobalShader.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "Helpers/GrantASCHelper.h"
#include "Kismet/KismetMathLibrary.h"

int32 UARPGAbilitySystemComponent::GetActivatableAbilityIndexBasedOnDynamicTag(
	const FGameplayTag& InInputTag)
{
	const auto Abilities = GetActivatableAbilities();
	const int AbilityIndex = Abilities.IndexOfByPredicate([&]
	(const FGameplayAbilitySpec& Ability)
		{
			return Ability.DynamicAbilityTags.HasTagExact(InInputTag);
		});
	return AbilityIndex;
}

void UARPGAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	const int Idx = GetActivatableAbilityIndexBasedOnDynamicTag(InInputTag);

	if (-1 == Idx)
	{
		return;
	}

	const FGameplayAbilitySpec& AbilityToManage = GetActivatableAbilities()[Idx];


	if (InInputTag.MatchesTag(ARPGGameplayTags::InputTag_Toggle) &&
		GetActivatableAbilities()[Idx].IsActive())
	{
		CancelAbilityHandle(GetActivatableAbilities()[Idx].Handle);

		return;
	}

	TryActivateAbility(AbilityToManage.Handle);
}

void UARPGAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(ARPGGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	const int Idx = GetActivatableAbilityIndexBasedOnDynamicTag(InInputTag);

	if (INDEX_NONE == Idx)
	{
		return;
	}

	if (GetActivatableAbilities()[Idx].IsActive())
	{
		CancelAbilityHandle(GetActivatableAbilities()[Idx].Handle);
	}
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
			continue;
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

	if (SpecPointers.IsEmpty())
	{
		return false;
	}

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

	const bool bAbility = TryActivateAbility(SpecPointers[Index]->Handle, true);

	return bAbility;
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
