// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ARPGAIController.h"

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

void AARPGAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Stimulus.WasSuccessfullySensed() || !Actor)
	{
		return;
	}

	//AGRO LOGIC
	checkf(GetBlackboardComponent(), TEXT("Blackboard component is invalid in %s"), *GetName());

	if (!UARPGFunctionLibrary::NativeDoesActorHaveTag(Actor, ARPGGameplayTags::Shared_Status_Death))
	{
		GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Actor);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);
	}
}

void AARPGAIController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	Super::SetGenericTeamId(InTeamID);
}

FGenericTeamId AARPGAIController::GetGenericTeamId() const
{
	return Super::GetGenericTeamId();
}

ETeamAttitude::Type AARPGAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	return Super::GetTeamAttitudeTowards(Other);
}

void AARPGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	checkf(BehaviorTree, TEXT("Behaviour tree is not set in %s"), *GetName());

	RunBehaviorTree(BehaviorTree);
}

void AARPGAIController::BeginPlay()
{
	Super::BeginPlay();
	UCrowdFollowingComponent* CrowdFC = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());

	CrowdFC->SetCrowdSimulationState(bShouldSimulateAvoidance
		                                 ? ECrowdSimulationState::Enabled
		                                 : ECrowdSimulationState::Disabled);

	CrowdFC->SetCrowdAvoidanceQuality(static_cast<ECrowdAvoidanceQuality::Type>(SimulationQuality));
	CrowdFC->SetAvoidanceGroup(GetGenericTeamId());
	CrowdFC->SetGroupsToAvoid(GetGenericTeamId());
	CrowdFC->SetCrowdCollisionQueryRange(AvoidanceRange, true);
	CrowdFC->SetCrowdSeparation(true, true);
}

AARPGAIController::AARPGAIController(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseConfig_Sight");
	SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	SenseConfig_Sight->SightRadius = 5000.f;
	SenseConfig_Sight->LoseSightRadius = 0.f;
	SenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	PerceptionComponent->ConfigureSense(*SenseConfig_Sight);
	PerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnPerceptionUpdated);

	AARPGAIController::SetGenericTeamId(FGenericTeamId{1});
}
