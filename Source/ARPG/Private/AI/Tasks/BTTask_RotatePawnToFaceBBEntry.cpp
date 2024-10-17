// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_RotatePawnToFaceBBEntry.h"

#include "AIController.h"
#include "DebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

namespace
{
	FORCEINLINE_DEBUGGABLE FVector::FReal CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB)
	{
		return (VectorA.IsNearlyZero() || VectorB.IsNearlyZero())
			       ? 1.f
			       : VectorA.CosineAngle2D(VectorB);
	}
}


UBTTask_RotatePawnToFaceBBEntry::UBTTask_RotatePawnToFaceBBEntry()
{
	NodeName = "Rotate Pawn to face BB entry";

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, BlackboardKey), AActor::StaticClass());
}

void UBTTask_RotatePawnToFaceBBEntry::PostInitProperties()
{
	Super::PostInitProperties();
	PrecisionCos = FMath::Cos(FMath::DegreesToRadians(Precision));
}

void UBTTask_RotatePawnToFaceBBEntry::PostLoad()
{
	Super::PostLoad();
	PrecisionCos = FMath::Cos(FMath::DegreesToRadians(Precision));
}

EBTNodeResult::Type UBTTask_RotatePawnToFaceBBEntry::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr || AIController->GetPawn() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FRotatePawnMemory* MyMemory = CastInstanceNodeMemory<FRotatePawnMemory>(NodeMemory);
	check(MyMemory);
	MyMemory->Reset();

	APawn* Pawn = AIController->GetPawn();
	AActor* TargetActor = Cast<AActor>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));

	MyMemory->OwnerPawn = Pawn;
	MyMemory->Target = TargetActor;

	if (!MyMemory->IsValid())
	{
		return EBTNodeResult::Failed;
	}

	const FVector PawnLocation = Pawn->GetActorLocation();
	const FVector::FReal AngleDifference = CalculateAngleDifferenceDot(PawnLocation,
	                                                                   TargetActor->GetActorLocation() - PawnLocation);

	if (HasReachedPrecision(NodeMemory))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

bool UBTTask_RotatePawnToFaceBBEntry::HasReachedPrecision(uint8* NodeMemory) const
{
	FRotatePawnMemory* MyMemory = CastInstanceNodeMemory<FRotatePawnMemory>(NodeMemory);
	check(MyMemory)

	const FVector PawnForwardVector = MyMemory->OwnerPawn->GetActorForwardVector();
	const FVector PawnLocation = MyMemory->OwnerPawn->GetActorLocation();
	const FVector TargetLocation = MyMemory->Target->GetActorLocation();
	return CalculateAngleDifferenceDot(PawnForwardVector, (TargetLocation - PawnLocation).GetSafeNormal()) >=
		PrecisionCos;
}

void UBTTask_RotatePawnToFaceBBEntry::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FRotatePawnMemory* MyMemory = CastInstanceNodeMemory<FRotatePawnMemory>(NodeMemory);
	check(MyMemory);

	if (!MyMemory->IsValid())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	if (HasReachedPrecision(NodeMemory))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	const FVector OwnerLocation = MyMemory->OwnerPawn->GetActorLocation();
	const FVector TargetLocation = MyMemory->Target->GetActorLocation();
	const FRotator FinalRotator = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);
	const FRotator LerpRot = UKismetMathLibrary::RInterpTo(MyMemory->OwnerPawn->GetActorRotation(), FinalRotator,
	                                                       DeltaSeconds,
	                                                       InterpSpeed);
	MyMemory->OwnerPawn->SetActorRotation(LerpRot);
}

void UBTTask_RotatePawnToFaceBBEntry::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                       EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FRotatePawnMemory>(NodeMemory, InitType);
}

void UBTTask_RotatePawnToFaceBBEntry::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                    EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FRotatePawnMemory>(NodeMemory, CleanupType);
}

void UBTTask_RotatePawnToFaceBBEntry::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                            EBTDescriptionVerbosity::Type Verbosity,
                                                            TArray<FString>& Values) const
{
	const FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc));

	FRotatePawnMemory* MyMemory = CastInstanceNodeMemory<FRotatePawnMemory>(NodeMemory);
	if (!MyMemory->IsValid())
	{
		Values.Add(TEXT("AI or target is nullptr"));
		return;
	}

	const FVector PawnLocation = MyMemory->OwnerPawn->GetActorLocation();
	const FVector TargetLocation = MyMemory->Target->GetActorLocation();

	const FVector::FReal AngleDifference = CalculateAngleDifferenceDot(PawnLocation, TargetLocation - PawnLocation);

	Values.Add(FString::Printf(
		TEXT("Current angle: %.2f"), FMath::RadiansToDegrees(FMath::Acos(AngleDifference))));
}

FString UBTTask_RotatePawnToFaceBBEntry::GetStaticDescription() const
{
	const FString KeyDescription = BlackboardKey.SelectedKeyName.ToString();
	return FString::Printf(
		TEXT("Smoothly rotates to face %s Key until the angle precision: %s is reached"), *KeyDescription,
		*FString::SanitizeFloat(Precision));
}
