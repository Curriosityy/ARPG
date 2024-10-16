// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_SetMotionWarpTarget.h"

#include "AIController.h"
#include "MotionWarpingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ARPGEnemyCharacter.h"
#include "GameFramework/Actor.h"

UBTService_SetMotionWarpTarget::UBTService_SetMotionWarpTarget()
{
	NodeName = "Native Set Motion Warp Target";

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	Interval = 1.f;
	RandomDeviation = 1.f;
	InTargetActorKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTService_SetMotionWarpTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	const UBlackboardData* BlackBoard = GetBlackboardAsset();

	if (!BlackBoard)
	{
		return;
	}

	InTargetActorKey.ResolveSelectedKey(*BlackBoard);
}

FString UBTService_SetMotionWarpTarget::GetStaticDescription() const
{
	return FString::Printf(TEXT("Set motion warping target to %s Key %s"), *InTargetActorKey.SelectedKeyName.ToString(),
	                       *GetStaticServiceDescription());
}

void UBTService_SetMotionWarpTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AARPGEnemyCharacter* const Enemy = Cast<AARPGEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	const AActor* TargetActor = Cast<AActor>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName));

	if (!Enemy || !TargetActor)
	{
		return;
	}

	Enemy->GetMotionWarpingComponent()->AddOrUpdateWarpTarget({
		FName("AttackTarget"), TargetActor->GetActorTransform()
	});
}
