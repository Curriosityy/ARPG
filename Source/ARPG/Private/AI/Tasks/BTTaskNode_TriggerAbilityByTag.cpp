// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTaskNode_TriggerAbilityByTag.h"

#include "AbilitySystemInterface.h"
#include "AIController.h"

UBTTaskNode_TriggerAbilityByTag::UBTTaskNode_TriggerAbilityByTag()
{
	NodeName = "Trigger Ability By Tag";
}

EBTNodeResult::Type UBTTaskNode_TriggerAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(AIController->GetPawn());
	checkf(ASI, TEXT("Trying to execute ability on AI without AbilitySystemInterface"));

	const bool bAbilityActivated = Cast<UARPGAbilitySystemComponent>(ASI->GetAbilitySystemComponent())->
		TryActivateAbilityByTagActivationPolicy(AbilityToActivate, ActivationPolicy);

	return bAbilityActivated ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

FString UBTTaskNode_TriggerAbilityByTag::GetStaticDescription() const
{
	return Super::GetStaticDescription() + FString::Printf(
		TEXT("\nTrigger Ability Tag %s Mode %s"), *AbilityToActivate.ToString(),
		*UEnum::GetValueAsName(ActivationPolicy).ToString());
}
