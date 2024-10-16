// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "ARPGBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	bool DoesOwnerHaveGameplayTag(const FGameplayTag Tag) const;
};
