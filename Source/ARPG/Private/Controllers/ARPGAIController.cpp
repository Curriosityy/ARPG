// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ARPGAIController.h"

#include "Navigation/CrowdFollowingComponent.h"

AARPGAIController::AARPGAIController(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
}
