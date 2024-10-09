// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGEnemyGameplayAbility.h"

#include "Characters/ARPGEnemyCharacter.h"

AARPGEnemyCharacter* UARPGEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!EnemyCharacter.IsValid())
	{
		EnemyCharacter = Cast<AARPGEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return EnemyCharacter.IsValid() ? EnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UARPGEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	if (!CombatComponent.IsValid())
	{
		CombatComponent = GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
	}

	return CombatComponent.IsValid() ? CombatComponent.Get() : nullptr;
}
