// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/MyDataAsset_EnemyStartUpData.h"

#include "AbilitySystem/Abilities/ARPGEnemyGameplayAbility.h"
#include "Helpers/GrantASCHelper.h"

void UMyDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(InASC, Level);
	TArray<FGameplayAbilitySpecHandle> _;
	GrantASCHelper::GrantASCHelper::GrantEnemyAbilities(StartupEnemyAbilities, InASC, 1, _);
}
