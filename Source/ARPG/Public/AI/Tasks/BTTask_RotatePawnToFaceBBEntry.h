// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RotatePawnToFaceBBEntry.generated.h"


struct FRotatePawnMemory
{
	TWeakObjectPtr<AActor> OwnerPawn = {};
	TWeakObjectPtr<AActor> Target = {};

	bool IsValid() const
	{
		return OwnerPawn.IsValid() && Target.IsValid();
	}

	void Reset()
	{
		OwnerPawn = nullptr;
		Target = nullptr;
	}
};

/**
 * 
 */
UCLASS()
class ARPG_API UBTTask_RotatePawnToFaceBBEntry : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float Precision = {10.f};
	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float InterpSpeed = {5};
	UPROPERTY()
	float PrecisionCos;

public:
	UBTTask_RotatePawnToFaceBBEntry();

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	                              EBTMemoryInit::Type InitType) const override;


	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	                           EBTMemoryClear::Type CleanupType) const override;

	FORCEINLINE virtual uint16 GetInstanceMemorySize() const override { return sizeof(FRotatePawnMemory); }

	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	                                   EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

	virtual FString GetStaticDescription() const override;
};
