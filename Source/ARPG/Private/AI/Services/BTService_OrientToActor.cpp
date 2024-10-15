// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_OrientToActor.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"


UBTService_OrientToActor::UBTService_OrientToActor()
{
	NodeName = "Native Orient Rotation To Target Actor";

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	Interval = 0.0f;
	RandomDeviation = 0.f;
	InTargetActorKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTService_OrientToActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	auto BlackBoard = GetBlackboardAsset();

	if (!BlackBoard)
	{
		return;
	}

	InTargetActorKey.ResolveSelectedKey(*BlackBoard);
}

FString UBTService_OrientToActor::GetStaticDescription() const
{
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("Orient rotation to %s key %s"), *KeyDescription, *GetStaticServiceDescription());
}

void UBTService_OrientToActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AActor* TargetActor = Cast<AActor>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName));

	APawn* AiPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!TargetActor || !AiPawn)
	{
		return;
	}

	const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(AiPawn->GetActorLocation(),
	                                                                  TargetActor->GetActorLocation());
	const FRotator TargetRot = FMath::RInterpTo(AiPawn->GetActorRotation(), LookAtRot,
	                                            DeltaSeconds, RotationInterpSpeed);
	AiPawn->SetActorRotation(TargetRot);
}
