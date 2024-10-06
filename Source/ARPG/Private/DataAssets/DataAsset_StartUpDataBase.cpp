// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

void UDataAsset_StartUpDataBase::GrantAbility(TSubclassOf<UARPGGameplayAbility> Ability,
                                              UARPGAbilitySystemComponent* InASC, int32 Level)
{
	checkf(Ability,TEXT("UDataAsset_StartUpDataBase::GrantAbility : ability is NULL"));
	checkf(InASC,TEXT("UDataAsset_StartUpDataBase::GrantAbility: InASC is NULL"));

	FGameplayAbilitySpec Spec{Ability};
	Spec.SourceObject=InASC->GetAvatarActor();
	Spec.Level = Level;
	
	InASC->GiveAbility(Spec);
}

void UDataAsset_StartUpDataBase::GrantAbilities(TArray<TSubclassOf<UARPGGameplayAbility>> AbilitiesToGrant,
	UARPGAbilitySystemComponent* InASC, int32 Level)
{
	for (const TSubclassOf<UARPGGameplayAbility>& ToGrant : AbilitiesToGrant)
	{
		GrantAbility(ToGrant, InASC, Level);
	}
}

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level)
{
	checkf(InASC,TEXT("UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent: InASC is NULL"));

	GrantAbilities(ReactiveAbilities, InASC, Level);
	GrantAbilities(StartupAbilitiesActivatedOnGiven, InASC, Level);
}
