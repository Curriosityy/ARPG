// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ARPGHeroWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"

void AARPGHeroWeapon::SetGrantedAbilities(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilities)
{
	GrantedAbilities = InGrantedAbilities;
}

TArray<FGameplayAbilitySpecHandle> AARPGHeroWeapon::GetGrantedAbilities() const
{
	return GrantedAbilities;
}

void AARPGHeroWeapon::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	Super::OnWeaponOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	if (!IsHitValid(OtherActor, WeaponOwningPawn) ||
		IsBlockValid(OtherActor, WeaponOwningPawn))
	{
		return;
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         ARPGGameplayTags::Player_Event_HitPause,
	                                                         {});
}
