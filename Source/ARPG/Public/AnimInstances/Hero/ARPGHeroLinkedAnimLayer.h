// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ARPGBaseAnimInstance.h"
#include "ARPGHeroLinkedAnimLayer.generated.h"


class UARPGHeroAnimInstance;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGHeroLinkedAnimLayer : public UARPGBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UARPGHeroAnimInstance* GetHeroAnimInstance() const;
};
