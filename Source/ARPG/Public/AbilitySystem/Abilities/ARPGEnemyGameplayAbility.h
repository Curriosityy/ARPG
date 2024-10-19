// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "Interfaces/OverHeadDebuggerInterface.h"
#include "ARPGEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AARPGEnemyCharacter;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGEnemyGameplayAbility : public UARPGGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<AARPGEnemyCharacter> EnemyCharacter;

	UPROPERTY()
	TWeakObjectPtr<UEnemyCombatComponent> CombatComponent;

public:
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
};
