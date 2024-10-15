// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ARPGAIController.generated.h"

class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGAIController : public AAIController
{
	GENERATED_BODY()

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess))
	// TObjectPtr<UAIPerceptionComponent> PerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess))
	TObjectPtr<UAISenseConfig_Sight> SenseConfig_Sight;

public:
	AARPGAIController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
