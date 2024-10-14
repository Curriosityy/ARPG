// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Items/Weapons/ARPGWeaponBase.h"
#include "Types/ARPGMessagesStruct.h"

void UPawnCombatComponent::AddCarriedWeapon(FGameplayTag WeaponTag, AARPGWeaponBase* Weapon, bool bAsEquipped)
{
	checkf(WeaponTag.IsValid(), TEXT("UPawnCombatComponent::AddCarriedWeapon : A WeaponTag is invalid"))
	checkf(!CarriedWeapons.Contains(WeaponTag),
	       TEXT("UPawnCombatComponent::AddCarriedWeapon : A tag %s has already added to list"), *WeaponTag.ToString())
	checkf(Weapon, TEXT("UPawnCombatComponent::AddCarriedWeapon : Weapon is nullptr"))

	CarriedWeapons.Add(WeaponTag, Weapon);

	if (bAsEquipped)
	{
		SetCurrentEquippedWeapon(WeaponTag);
	}

	Debug::Print(FString::Printf(
		TEXT("Registered weapon %s name %s, auto equip %i"), *WeaponTag.ToString(), *Weapon->GetName(), bAsEquipped));
}

AARPGWeaponBase* UPawnCombatComponent::GetCarriedWeapon(FGameplayTag WeaponTag) const
{
	if (!CarriedWeapons.Contains(WeaponTag))
	{
		ensureMsgf(false, TEXT("Trying to get not existed weapon in inventory"));
		return nullptr;
	}

	return CarriedWeapons[WeaponTag];
}

AARPGWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeapon.IsValid())
	{
		ensureMsgf(false, TEXT("Trying to get current equipped weapon when Invalid"));
		return nullptr;
	}

	return GetCarriedWeapon(CurrentEquippedWeapon);
}

void UPawnCombatComponent::OnWeaponHit(AActor* ActorHitted, AActor* HittedBy)
{
	Debug::Print(FString::Printf(TEXT("OnWeaponHit")));
	FGameplayEventData data;
	data.Instigator = GetOwner();
	data.Target = ActorHitted;

	if (HittedList.Contains(ActorHitted))
	{
		return;
	}

	HittedList.Add(ActorHitted);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwner(),
		ARPGGameplayTags::Shared_Event_MeleeHit,
		data);
}

void UPawnCombatComponent::OnWeaponEndOverlap(AActor* ActorHitted, AActor* HittedBy)
{
	Debug::Print(FString::Printf(TEXT("OnWeaponEndOverlap")));
	HittedList.Remove(ActorHitted);
}

void UPawnCombatComponent::SetupEvents(FGameplayTag OldEquipedWeapon, FGameplayTag WeaponToEquip)
{
	if (OldEquipedWeapon.IsValid())
	{
		auto weapon = GetCarriedWeapon(OldEquipedWeapon);
		weapon->OnStartHit.RemoveDynamic(this, &UPawnCombatComponent::OnWeaponHit);
		weapon->OnEndHit.RemoveDynamic(this, &UPawnCombatComponent::OnWeaponEndOverlap);
	}

	if (WeaponToEquip.IsValid())
	{
		auto weapon = GetCarriedWeapon(WeaponToEquip);
		weapon->OnStartHit.AddDynamic(this, &UPawnCombatComponent::OnWeaponHit);
		weapon->OnEndHit.AddDynamic(this, &UPawnCombatComponent::OnWeaponEndOverlap);
	}
}

void UPawnCombatComponent::SetCurrentEquippedWeapon(FGameplayTag WeaponToEquip)
{
	SetupEvents(CurrentEquippedWeapon, WeaponToEquip);
	CurrentEquippedWeapon = WeaponToEquip;
	UGameplayMessageSubsystem::Get(this)
		.BroadcastMessage(ARPGGameplayTags::Message_WeaponChanged,
		                  FWeaponChanged{GetOwner(), GetCarriedWeapon(WeaponToEquip)});
}

void UPawnCombatComponent::ToggleCurrentWeaponCollider(bool Toggle, int ToggleType)
{
	checkf(CurrentEquippedWeapon.IsValid(), TEXT("Current Equipped weapon tag is invalid"));
	AARPGWeaponBase* CurrentWeapon = GetCurrentEquippedWeapon();
	checkf(CurrentWeapon, TEXT("Current Equipped weapon is nullptr"))
	CurrentWeapon->ToggleCollider(Toggle, ToggleType);
}
