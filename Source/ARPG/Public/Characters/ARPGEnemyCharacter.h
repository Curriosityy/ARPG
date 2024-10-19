// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Characters/ARPGBaseCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Interfaces/OverHeadDebuggerInterface.h"
#include "ARPGEnemyCharacter.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGEnemyCharacter : public AARPGBaseCharacter, public IOverHeadDebuggerInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DebugUI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> DebugWidgetComponent = {};

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

	virtual void HandleDeath_Implementation(const TSoftObjectPtr<UNiagaraSystem>& NiagaraSystemToPlay) override;

	virtual void SetOverHeadDebugText(const FString& Msg) override;
};
