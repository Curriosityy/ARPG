// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AARPGHeroWeapon;
/**
 * 
 */
UCLASS()
class ARPG_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	AARPGHeroWeapon* GetHeroCarriedWeapon(FGameplayTag Tag) const;
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	AARPGHeroWeapon* GetHeroCurrentWeapon() const;

	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	float GetCurrenHeroWeaponDamageAtLevel(int Level) const;

	virtual void OnWeaponHit(AActor* ActorHitted, AActor* HittedBy) override;
};
