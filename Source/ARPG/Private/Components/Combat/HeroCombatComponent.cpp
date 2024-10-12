// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"
#include "Items/Weapons/ARPGHeroWeapon.h"

AARPGHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeapon(FGameplayTag Tag) const
{
	return Cast<AARPGHeroWeapon>(GetCarriedWeapon(Tag));
}

AARPGHeroWeapon* UHeroCombatComponent::GetHeroCurrentWeapon() const
{
	return Cast<AARPGHeroWeapon>(GetCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetCurrenHeroWeaponDamageAtLevel(int Level) const
{
	return GetHeroCurrentWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(Level);
}

void UHeroCombatComponent::OnWeaponHit(AActor* ActorHitted, AActor* HittedBy)
{
	Super::OnWeaponHit(ActorHitted, HittedBy);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         ARPGGameplayTags::Player_Event_HitPause,
	                                                         {});
}
