// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TriggerAbilityByClass.generated.h"

class UARPGGameplayAbility;
/**
 * 
 */
UCLASS()
class ARPG_API UBTTask_TriggerAbilityByClass : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities", meta=(AllowPrivateAccess))
	TSubclassOf<UARPGGameplayAbility> AbilityToActivate;

public:
	UBTTask_TriggerAbilityByClass();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FName GetFNameForStatID() const override;
	GetName
};
