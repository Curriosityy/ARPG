// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARPGMovementComponentBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGMovementComponentBase : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UARPGMovementComponentBase();
	virtual float GetMaxSpeed() const override;
};
