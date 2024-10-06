// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ARPGBaseAnimInstance.h"
#include "ARPGCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AARPGBaseCharacter;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGCharacterAnimInstance : public UARPGBaseAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AARPGBaseCharacter> OwningCharacter = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> MovementComponent = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category="AnimData|LocomotionData")
	FVector Velocity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
