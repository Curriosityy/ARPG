// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGWeaponBase.generated.h"

class UMeshComponent;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHit, AActor*, ActorHitted, AActor*, HittedBy);

UCLASS()
class ARPG_API AARPGWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> WeaponMesh = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	TObjectPtr<UBoxComponent> WeaponCollider = {};

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	FName HandSocketToAttachTo{};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta=(AllowPrivateAccess))
	FName BackSocketToAttachTo{};

	void SendHitEventToOwner(AActor* OtherActor) const;

	UFUNCTION()
	virtual void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);


	UFUNCTION()
	virtual void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                UPrimitiveComponent* OtherComp, int OtherBodyIndex);


	static bool IsHitValid(AActor* OtherActor, APawn* WeaponOwningPawn);
	static bool IsBlockValid(AActor* OtherActor, APawn* WeaponOwningPawn);
	void SendBlockValidToDefender(AActor* OtherActor);

public:
	FOnHit OnStartHit;
	FOnHit OnEndHit;

	AARPGWeaponBase();

	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponCollider() const { return WeaponCollider; }

	/*int32 Type is used when other colliders are toggled in different animations, like fisting fight when,
	 *we want once left fist collision,once right weapon collision*/
	virtual void ToggleCollider(bool Toggle, int32 Type);

	UBoxComponent* GetWeaponCollider() { return WeaponCollider; }

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	virtual void Equip(UMeshComponent* Mesh);
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	virtual void UnEquip(UMeshComponent* Mesh);
	// Sets default values for this actor's properties
};
