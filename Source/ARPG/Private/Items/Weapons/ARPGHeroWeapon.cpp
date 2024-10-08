// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ARPGHeroWeapon.h"

void AARPGHeroWeapon::SetGrantedAbilities(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilities)
{
	GrantedAbilities = InGrantedAbilities;
}

TArray<FGameplayAbilitySpecHandle> AARPGHeroWeapon::GetGrantedAbilities() const
{
	return GrantedAbilities;
}
