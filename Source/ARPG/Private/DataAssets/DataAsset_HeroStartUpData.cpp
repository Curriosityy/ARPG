// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

bool FARPGGeroAbilitySet::IsValid() const
{
	return AbilityToGrant && InputTag.IsValid();
}

void UDataAsset_HeroStartUpData::GrantHeroAbility(const FARPGGeroAbilitySet& ToGrant,
                                                  UARPGAbilitySystemComponent* InAsc, int32 Level)
{
	FGameplayAbilitySpec AbilitySpec{ToGrant.AbilityToGrant};
	AbilitySpec.SourceObject = InAsc->GetAvatarActor();
	AbilitySpec.Level = Level;
	AbilitySpec.DynamicAbilityTags.AddTag(ToGrant.InputTag);

	InAsc->GiveAbility(AbilitySpec);
}

void UDataAsset_HeroStartUpData::GrantHeroAbilities(TArray<FARPGGeroAbilitySet>& AbilitiesToGrant,
                                                    UARPGAbilitySystemComponent* InAsc, const int32 Level)
{
	for (FARPGGeroAbilitySet& ToGrant : AbilitiesToGrant)
	{
		if (!ToGrant.IsValid())
		{
			continue;
		}

		GrantHeroAbility(ToGrant, InAsc, Level);
	}
}

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	Super::GiveToAbilitySystemComponent(InASC, Level);

	GrantHeroAbilities(HeroStartupAbilitySets, InASC, Level);
}
