// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGHeroGameplayAbility.h"

#include "Characters/ARPGHeroCharacter.h"
#include "Controllers/ARPGHeroController.h"

AARPGHeroCharacter* UARPGHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter = Cast<AARPGHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

AARPGHeroController* UARPGHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController = Cast<AARPGHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UARPGHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	if (!GetHeroCharacterFromActorInfo())
	{
		return nullptr;
	}

	if (!CachedHeroCombatComponent.IsValid())
	{
		CachedHeroCombatComponent = GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
	}

	return CachedHeroCombatComponent.IsValid() ? CachedHeroCombatComponent.Get() : nullptr;
}
