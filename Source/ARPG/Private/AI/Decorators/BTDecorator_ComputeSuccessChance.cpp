// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/BTDecorator_ComputeSuccessChance.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTDecorator_ComputeSuccessChance::UBTDecorator_ComputeSuccessChance()
{
	bCreateNodeInstance = false;
}

bool UBTDecorator_ComputeSuccessChance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                   uint8* NodeMemory) const
{
	return UKismetMathLibrary::RandomBoolWithWeight(
		UKismetMathLibrary::RandomFloatInRange(SuccessChanceMin, SuccessChanceMax));
}

FString UBTDecorator_ComputeSuccessChance::GetStaticDescription() const
{
	return Super::GetStaticDescription() + FString::Printf(
		TEXT("\nSuccess Chance Min %f \n Success Chance Max %f"), SuccessChanceMin, SuccessChanceMax);
}
