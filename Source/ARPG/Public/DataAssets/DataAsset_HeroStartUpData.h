// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "Types/ARPGStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"


/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartupData",
		meta=(Title="InputTag", AllowPrivateAccess, Categories="InputTag"))
	TArray<FARPGHeroAbilitySet> HeroStartupAbilitySets = {};

public:
	static void GrantHeroAbility(const FARPGHeroAbilitySet& ToGrant, UARPGAbilitySystemComponent* InAsc, int32 INT32);
	static void GrantHeroAbilities(TArray<FARPGHeroAbilitySet>& Array, UARPGAbilitySystemComponent* InAsc, int32 INT32);
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level) override;
};
