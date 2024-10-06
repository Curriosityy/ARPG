// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ARPGWeaponBase.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AARPGWeaponBase::AARPGWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>("WeaponCollider");
	WeaponCollider->SetupAttachment(GetRootComponent());
	WeaponCollider->SetBoxExtent({20.f,20.f,20.f});
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

