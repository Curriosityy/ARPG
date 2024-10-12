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
	UPROPERTY()
	FProperty* AttackPower;

public:
	UGEExecCalc_damageTaken();
};
