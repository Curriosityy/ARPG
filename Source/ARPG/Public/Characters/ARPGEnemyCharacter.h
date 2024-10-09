// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ARPGBaseCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "ARPGEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AARPGEnemyCharacter : public AARPGBaseCharacter
{
	GENERATED_BODY()

public:
	AARPGEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const
	{
		return Cast<UEnemyCombatComponent>(GetCombatComponent());
	}

	virtual void PossessedBy(AController* NewController) override;

private:
	void InitEnemyStatupData();
};
