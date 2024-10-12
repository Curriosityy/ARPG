// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_damageTaken.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UGEExecCalc_damageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEExecCalc_damageTaken();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
