// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class ARPG_API AARPGWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> WeaponMesh = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	TObjectPtr<UBoxComponent> WeaponCollider = {};

public:
	AARPGWeaponBase();
	
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponCollider() const { return WeaponCollider; }

	// Sets default values for this actor's properties
};
