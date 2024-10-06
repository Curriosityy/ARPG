// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AARPGWeaponBase;
/**
 * 
 */
UCLASS()
class ARPG_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, TObjectPtr<AARPGWeaponBase>> CarriedWeapons = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FGameplayTag CurrentEquippedWeapon = {};

public:
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	void AddCarriedWeapon(FGameplayTag WeaponTag, AARPGWeaponBase* Weapon, bool bAsEquipped = false);
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	AARPGWeaponBase* GetCarriedWeapon(FGameplayTag weaponTag);
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	AARPGWeaponBase* GetCurrentEquippedWeapon();
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	void SetCurrentEquippedWeapon(FGameplayTag WeaponToEquip);
};
