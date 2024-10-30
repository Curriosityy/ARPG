// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/ARPGWeaponBase.h"
#include "ARPGDualWieldingWeapon.generated.h"

class UMeshComponent;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGDualWieldingWeapon : public AARPGWeaponBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	FName SecondWeaponHandSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	FName SecondWeaponBackSocket;

	UPROPERTY()
	TObjectPtr<AARPGDualWieldingWeapon> SecondWeapon;

	bool bIsSubWeapon = false;

public:
	AARPGDualWieldingWeapon();

	virtual void BeginPlay() override;

	virtual void Equip(UMeshComponent* Mesh) override;
	virtual void UnEquip(UMeshComponent* Mesh) override;

	virtual void ToggleCollider(bool Toggle, int32 Type) override;
};
