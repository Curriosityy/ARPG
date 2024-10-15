// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ARPGAIController.h"

#include "DebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

void AARPGAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
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
