// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ARPGWeaponBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "GameplayTagAssetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "GameFramework/Pawn.h"

void AARPGWeaponBase::SendHitEventToOwner(AActor* OtherActor) const
{
	FGameplayEventData data;
	data.Instigator = GetOwner();
	data.Target = OtherActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwner(),
		ARPGGameplayTags::Shared_Event_MeleeHit,
		data);
}

bool AARPGWeaponBase::IsHitValid(AActor* OtherActor, APawn* WeaponOwningPawn)
{
	if (Cast<IGenericTeamAgentInterface>(WeaponOwningPawn)->
		GetTeamAttitudeTowards(*OtherActor) == ETeamAttitude::Friendly)
	{
		//Hit friend
		return false;
	}

	if (!Cast<IAbilitySystemInterface>(OtherActor))
	{
		//Hitted wall without ASC WALL,Other weapon ETC.
		return false;
	}

	return true;
}

bool AARPGWeaponBase::IsBlockValid(AActor* OtherActor, const APawn* WeaponOwningPawn)
{
	FGameplayTag blockTag = ARPGGameplayTags::Shared_Status_Blocking;
	bool bIsPlayerBlocking = UARPGFunctionLibrary::NativeDoesActorHaveTag(OtherActor, blockTag);
	bool bIsBlockValid = false;

	if (bIsPlayerBlocking)
	{
		bIsBlockValid = UARPGFunctionLibrary::GetHitDirection(OtherActor, WeaponOwningPawn, 60) ==
			EARPGHitDirection::Front;
	}

	return bIsBlockValid;
}

void AARPGWeaponBase::SendBlockValidToDefender(AActor* OtherActor)
{
	FGameplayEventData data;
	data.Instigator = GetOwner();
	data.Target = OtherActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor,
	                                                         ARPGGameplayTags::Shared_Event_SuccessfulBlock,
	                                                         data);
}

void AARPGWeaponBase::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Weapon have not setted Instigator as owning pawn of the weapon %s"), *GetName())

	if (!IsHitValid(OtherActor, WeaponOwningPawn))
	{
		return;
	}


	if (IsBlockValid(OtherActor, WeaponOwningPawn))
	{
		SendBlockValidToDefender(OtherActor);
		return;
	}

	SendHitEventToOwner(OtherActor);
}

void AARPGWeaponBase::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Weapon have not setted Instigator as owning pawn of the weapon %s"), *GetName())

	if (Cast<IGenericTeamAgentInterface>(WeaponOwningPawn)->
		GetTeamAttitudeTowards(*OtherActor) == ETeamAttitude::Friendly)
	{
		//Hit friend
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
