// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_TriggerAbilityByClass.h"

#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "DebugHelper.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

UBTTask_TriggerAbilityByClass::UBTTask_TriggerAbilityByClass()
{
	NodeName = "Trigger Ability By Class";
}

EBTNodeResult::Type UBTTask_TriggerAbilityByClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(AIController->GetPawn());
	checkf(ASI, TEXT("Trying to execute ability on AI without AbilitySystemInterface"));

	const bool bAbilityActivated = Cast<UARPGAbilitySystemComponent>(ASI->GetAbilitySystemComponent())->
		TryActivateAbilityByClassActivationPolicy(AbilityToActivate, ActivationPolicy);

	return bAbilityActivated ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

FString UBTTask_TriggerAbilityByClass::GetStaticDescription() const
{
	FString AbilityName = AbilityToActivate ? AbilityToActivate->GetName() : "Nullptr";
	return Super::GetStaticDescription() + FString::Printf(
		TEXT("\nTrigger Ability %s Mode %s"), *AbilityName,
		*UEnum::GetValueAsName(ActivationPolicy).ToString());
}
