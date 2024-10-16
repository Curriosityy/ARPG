// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_TriggerAbilityByClass.h"

#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

UBTTask_TriggerAbilityByClass::UBTTask_TriggerAbilityByClass()
{
	NodeName = "Trigger Ability By Class";
}

EBTNodeResult::Type UBTTask_TriggerAbilityByClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();

	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(AIController->GetPawn());
	checkf(ASI, TEXT("Trying to execute ability on AI without AbilitySystemInterface"));

	bool abilityActivated = Cast<UARPGAbilitySystemComponent>(ASI->GetAbilitySystemComponent())->
		TryActivateAbilityByClass(AbilityToActivate);

	return abilityActivated ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

FName UBTTask_TriggerAbilityByClass::GetFNameForStatID() const
{
	return FName(FString::Printf(TEXT("Trigger Ability %s"), *AbilityToActivate->GetName()));
}
