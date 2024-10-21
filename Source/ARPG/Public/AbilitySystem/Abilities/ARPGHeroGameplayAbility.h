// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "ARPGHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AARPGHeroController;
class AARPGHeroCharacter;
/**
 * 
 */
UCLASS(Abstract)
class ARPG_API UARPGHeroGameplayAbility : public UARPGGameplayAbility
{
	GENERATED_BODY()
	UPROPERTY()
	TWeakObjectPtr<AARPGHeroCharacter> CachedHeroCharacter;

	UPROPERTY()
	TWeakObjectPtr<AARPGHeroController> CachedHeroController;

	UPROPERTY()
	TWeakObjectPtr<UHeroCombatComponent> CachedHeroCombatComponent;

public:
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
};
