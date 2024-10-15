// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ARPGBaseCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "ARPGEnemyCharacter.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGEnemyCharacter : public AARPGBaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent = {};

public:
	AARPGEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE virtual UEnemyCombatComponent* GetEnemyCombatComponent() const
	{
		return Cast<UEnemyCombatComponent>(GetCombatComponent());
	}

	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;

private:
	void InitEnemyStatupData();
};
