// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "DebugHelper.h"
#include "Items/Weapons/ARPGWeaponBase.h"

void UPawnCombatComponent::AddCarriedWeapon(FGameplayTag WeaponTag, AARPGWeaponBase* Weapon, bool bAsEquipped)
{
	checkf(WeaponTag.IsValid(), TEXT("UPawnCombatComponent::AddCarriedWeapon : A WeaponTag is invalid"))
	checkf(!CarriedWeapons.Contains(WeaponTag),
	       TEXT("UPawnCombatComponent::AddCarriedWeapon : A tag %s has already added to list"), *WeaponTag.ToString())
	checkf(Weapon, TEXT("UPawnCombatComponent::AddCarriedWeapon : Weapon is nullptr"))

	CarriedWeapons.Add(WeaponTag, Weapon);

	if (bAsEquipped)
	{
		CurrentEquippedWeapon = WeaponTag;
	}

	Debug::Print(FString::Printf(
		TEXT("Registered weapon %s name %s, auto equip %i"), *WeaponTag.ToString(), *Weapon->GetName(), bAsEquipped));
}

AARPGWeaponBase* UPawnCombatComponent::GetCarriedWeapon(FGameplayTag WeaponTag)
{
	if (!CarriedWeapons.Contains(WeaponTag))
	{
		ensureMsgf(false, TEXT("Trying to get not existed weapon in inventory"));
		return nullptr;
	}

	return CarriedWeapons[WeaponTag];
}

AARPGWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon()
{
	if (!CurrentEquippedWeapon.IsValid())
	{
		ensureMsgf(false, TEXT("Trying to get current equipped weapon when Invalid"));
		return nullptr;
	}

	return GetCarriedWeapon(CurrentEquippedWeapon);
}

void UPawnCombatComponent::SetCurrentEquippedWeapon(FGameplayTag WeaponToEquip)
{
	CurrentEquippedWeapon = WeaponToEquip;
}
