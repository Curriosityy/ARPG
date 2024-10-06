// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ARPGCharacterAnimInstance.h"
#include "ARPGHeroAnimInstance.generated.h"

class AARPGHeroCharacter;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGHeroAnimInstance : public UARPGCharacterAnimInstance
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AARPGHeroCharacter> OwningHeroCharacter = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category="AnimData|LocomotionData")
	bool bShouldEnderRelaxState = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="AnimData|LocomotionData")
	float EnterRelaxedStateThreshold = {5.f};

	float ElapsedIdleTime = {};
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
