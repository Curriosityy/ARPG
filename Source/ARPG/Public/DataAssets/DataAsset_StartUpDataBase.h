// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UARPGAbilitySystemComponent;
class UARPGGameplayAbility;
/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,Category="StartupData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly,Category="StartupData")
	TArray<TSubclassOf<UARPGGameplayAbility>> StartupAbilitiesActivatedOnGiven;
	
protected:
	static void GrantAbility(TSubclassOf<UARPGGameplayAbility> Ability,UARPGAbilitySystemComponent* InASC, int32 Level = 1);
	static void GrantAbilities(TArray<TSubclassOf<UARPGGameplayAbility>> AbilitiesToGrant,UARPGAbilitySystemComponent* InASC, int32 Level = 1);
public:
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level = 1);
};