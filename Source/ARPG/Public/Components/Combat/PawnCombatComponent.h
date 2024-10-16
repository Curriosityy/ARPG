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
	AARPGWeaponBase* GetCarriedWeapon(FGameplayTag weaponTag) const;
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	AARPGWeaponBase* GetCurrentEquippedWeapon() const;

	UFUNCTION()
	virtual void OnWeaponHit(AActor* ActorHitted, AActor* HittedBy);
	UFUNCTION()
	void OnWeaponEndOverlap(AActor* ActorHitted, AActor* HittedBy);

	void SetupEvents(FGameplayTag OldEquipedWeapon, FGameplayTag WeaponToEquip);

	UFUNCTION(BlueprintCallable, Category="ARPG|Combat")
	void SetCurrentEquippedWeapon(FGameplayTag WeaponToEquip);
	UFUNCTION(BlueprintCallable, Category="ARPG|Combat", meta=(ToggleType=-1))
	void ToggleCurrentWeaponCollider(bool Toggle, int ToggleType);
};
