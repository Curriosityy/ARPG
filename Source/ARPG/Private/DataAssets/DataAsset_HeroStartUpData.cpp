// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "Helpers/GrantAbilityHelper.h"


void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	Super::GiveToAbilitySystemComponent(InASC, Level);

	GrantAbilityHelper::GrantAbilityHelper::GrantHeroAbilities(HeroStartupAbilitySets, InASC, Level);
}
