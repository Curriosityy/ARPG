// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ComputeSuccessChance.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBTDecorator_ComputeSuccessChance : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behavior",
		meta=(AllowPrivateAccess, UIMin=0, ClampMin=0, ClampMax=1, UIMax=1))
	float SuccessChanceMin = {.5f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behavior",
		meta=(AllowPrivateAccess, UIMin=0, ClampMin=0, ClampMax=1, UIMax=1))
	float SuccessChanceMax = {.7f};

public:
	UBTDecorator_ComputeSuccessChance();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
};
