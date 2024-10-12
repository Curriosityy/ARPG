// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "ARPGStructTypes.generated.h"

struct FScalableFloat;
class UARPGGameplayAbility;
class UInputAction;
class UARPGHeroGameplayAbility;
class UInputMappingContext;
class UARPGHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FARPGInputConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (Categories="InputTag"))
	FGameplayTag InputTag = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = {};

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FARPGHeroAbilitySet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InputTag", meta = (Categories = "InputTag"))
	FGameplayTag InputTag = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InputTag")
	TSubclassOf<UARPGHeroGameplayAbility> AbilityToGrant = {};

	bool IsValid() const;
};


USTRUCT(BlueprintType)
struct ARPG_API FARPGHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGHeroLinkedAnimLayer> WeaponAnimLayerToLink = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag", Categories="InputTag"))
	TArray<FARPGHeroAbilitySet> AbilitiesToGrant = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> WeaponMappingContext = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
};
