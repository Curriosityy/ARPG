// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "UObject/NoExportTypes.h"
#include "InputActionValueDTO.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UInputActionValueDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FInputActionValue Value;
};
