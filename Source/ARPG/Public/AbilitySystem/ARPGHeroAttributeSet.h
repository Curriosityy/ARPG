// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "ARPGHeroAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGHeroAttributeSet : public UARPGAttributeSet
{
	GENERATED_BODY()

public:
	UARPGHeroAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category="Rage", ReplicatedUsing = OnRep_CurrentRage)
	FGameplayAttributeData CurrentRage = {};
	ATTRIBUTE_ACCESSORS(ThisClass, CurrentRage);

	UPROPERTY(BlueprintReadOnly, Category="Rage", ReplicatedUsing = OnRep_MaxRage)
	FGameplayAttributeData MaxRage = {};
	ATTRIBUTE_ACCESSORS(ThisClass, MaxRage);

	UFUNCTION()
	void OnRep_CurrentRage(const FGameplayAttributeData& OldRage);
	UFUNCTION()
	void OnRep_MaxRage(const FGameplayAttributeData& OldRage);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};