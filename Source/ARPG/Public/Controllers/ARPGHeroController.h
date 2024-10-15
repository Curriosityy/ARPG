// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "ARPGHeroController.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	FGenericTeamId CurrentTeamID;

public:
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
};
