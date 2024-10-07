// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/ARPGWeaponBase.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroWeapon : public AARPGWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FARPGHeroWeaponData HeroWeaponData;
};
