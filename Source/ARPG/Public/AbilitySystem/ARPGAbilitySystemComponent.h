// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ARPGAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	const FGameplayAbilitySpec& GetAbilitySpecBasedOnDynamicTag(const FGameplayTag& InInputTag);
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
};
