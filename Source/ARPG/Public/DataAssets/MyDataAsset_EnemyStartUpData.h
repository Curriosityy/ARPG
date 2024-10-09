// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "MyDataAsset_EnemyStartUpData.generated.h"

class UARPGEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class ARPG_API UMyDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartupData",
		meta=(AllowPrivateAccess))
	TArray<TSubclassOf<UARPGEnemyGameplayAbility>> StartupEnemyAbilities = {};

public:
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level) override;
};
