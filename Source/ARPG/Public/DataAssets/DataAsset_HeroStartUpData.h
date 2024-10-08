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
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level) override;
};
