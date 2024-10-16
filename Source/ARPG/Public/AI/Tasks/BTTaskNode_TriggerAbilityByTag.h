// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_TriggerAbilityByTag.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBTTaskNode_TriggerAbilityByTag : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities",
		meta=(AllowPrivateAccess, Categories="Enemy.Ability"))
	FGameplayTag AbilityToActivate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities", meta=(AllowPrivateAccess))
	FActivationPolicy ActivationPolicy = {FActivationPolicy::First};

public:
	UBTTaskNode_TriggerAbilityByTag();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
