// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
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
}

AARPGWeaponBase* UPawnCombatComponent::GetCarriedWeapon(FGameplayTag WeaponTag) const
{
	if (!CarriedWeapons.Contains(WeaponTag))
	{
		return nullptr;
	}

	return CarriedWeapons[WeaponTag];
}

AARPGWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeapon.IsValid())
	{
		return nullptr;
	}

	return GetCarriedWeapon(CurrentEquippedWeapon);
}


void UPawnCombatComponent::SetupEvents(FGameplayTag OldEquipedWeapon, FGameplayTag WeaponToEquip)
{
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
