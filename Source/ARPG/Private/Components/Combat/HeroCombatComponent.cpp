// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/ARPGHeroWeapon.h"

AARPGHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeapon(FGameplayTag Tag) const
{
	return Cast<AARPGHeroWeapon>(GetCarriedWeapon(Tag));
}
