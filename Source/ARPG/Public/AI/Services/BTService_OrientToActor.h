// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToActor.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBTService_OrientToActor : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Target")
	FBlackboardKeySelector InTargetActorKey = {};

	UPROPERTY(EditAnywhere, Category="Rotation")
	float RotationInterpSpeed = {5.f};

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual FString GetStaticDescription() const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UBTService_OrientToActor();
};
