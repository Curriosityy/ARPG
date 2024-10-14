// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "Helpers/GrantASCHelper.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, const int32 Level)
{
	checkf(InASC, TEXT("UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent: InASC is NULL"));
	TArray<FGameplayAbilitySpecHandle> _;
	GrantASCHelper::GrantASCHelper::GrantAbilities(StartupAbilitiesActivatedOnGiven, InASC, Level, _);
	GrantASCHelper::GrantASCHelper::GrantAbilities(ReactiveAbilities, InASC, Level, _);
	GrantASCHelper::GrantASCHelper::GrantGameplayEffectsToSelf(StartupGameplayEffects, InASC, Level);
}
