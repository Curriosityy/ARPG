// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ARPGWeaponBase.h"

#include "DebugHelper.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"

void AARPGWeaponBase::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Weapon have not setted Instigator as owning pawn of the weapon %s"), *GetName())

	if (OtherActor == WeaponOwningPawn)
	{
		//Hit ourself
		return;
	}

	OnStartHit.Broadcast(OtherActor, WeaponOwningPawn);
}

void AARPGWeaponBase::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Weapon have not setted Instigator as owning pawn of the weapon %s"), *GetName())

	if (OtherActor == WeaponOwningPawn)
	{
		//Hit ourself
		return;
	}

	OnEndHit.Broadcast(OtherActor, WeaponOwningPawn);
}

// Sets default values
AARPGWeaponBase::AARPGWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>("WeaponCollider");
	WeaponCollider->SetupAttachment(GetRootComponent());
	WeaponCollider->SetBoxExtent({20.f, 20.f, 20.f});
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollider->SetCollisionResponseToAllChannels(ECR_Overlap);
	WeaponCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnWeaponOverlap);
	WeaponCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnWeaponEndOverlap);
}

void AARPGWeaponBase::ToggleCollider(bool Toggle, int32 Type = -1)
{
	WeaponCollider->SetCollisionEnabled(Toggle ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}
