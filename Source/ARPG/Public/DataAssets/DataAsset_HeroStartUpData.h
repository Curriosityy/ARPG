// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FARPGGeroAbilitySet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InputTag")
	FGameplayTag InputTag = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InputTag")
	TSubclassOf<UARPGGameplayAbility> AbilityToGrant = {};

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartupData", meta=(Title="InputTag", AllowPrivateAccess))
	TArray<FARPGGeroAbilitySet> HeroStartupAbilitySets = {};

public:
	static void GrantHeroAbility(const FARPGGeroAbilitySet& ToGrant, UARPGAbilitySystemComponent* InAsc, int32 INT32);
	static void GrantHeroAbilities(TArray<FARPGGeroAbilitySet>& Array, UARPGAbilitySystemComponent* InAsc, int32 INT32);
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASC, int32 Level) override;
};
