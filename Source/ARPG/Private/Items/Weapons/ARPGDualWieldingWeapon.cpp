// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ARPGDualWieldingWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "Engine/World.h"

AARPGDualWieldingWeapon::AARPGDualWieldingWeapon()
{
}

void AARPGDualWieldingWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (!SecondWeapon)
	{
		FActorSpawnParameters params;
		params.Instigator = GetInstigator();
		params.Owner = Owner;

		SecondWeapon = GetWorld()->SpawnActorDeferred<AARPGDualWieldingWeapon>(GetClass(),
		                                                                       GetTransform(),
		                                                                       GetOwner(),
		                                                                       GetInstigator(),
		                                                                       ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
		                                                                       ESpawnActorScaleMethod::OverrideRootScale);
		SecondWeapon->SecondWeapon = this;
		SecondWeapon->bIsSubWeapon = true;
		SecondWeapon->HandSocketToAttachTo = SecondWeaponHandSocket;
		SecondWeapon->SecondWeaponBackSocket = SecondWeaponBackSocket;

		SecondWeapon->FinishSpawning(GetTransform());
	}
}

void AARPGDualWieldingWeapon::Equip(UMeshComponent* Mesh)
{
	Super::Equip(Mesh);

	if (!bIsSubWeapon)
	{
		SecondWeapon->Equip(Mesh);
	}
}

void AARPGDualWieldingWeapon::UnEquip(UMeshComponent* Mesh)
{
	Super::UnEquip(Mesh);

	if (!bIsSubWeapon)
	{
		SecondWeapon->UnEquip(Mesh);
	}
}
