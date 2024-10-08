// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "Helpers/GrantAbilityHelper.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	checkf(InASC, TEXT("UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent: InASC is NULL"));

	GrantAbilityHelper::GrantAbilityHelper::GrantAbilities(ReactiveAbilities, InASC, Level);
	GrantAbilityHelper::GrantAbilityHelper::GrantAbilities(StartupAbilitiesActivatedOnGiven, InASC, Level);
}
