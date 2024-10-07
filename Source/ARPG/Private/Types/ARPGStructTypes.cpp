// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/ARPGStructTypes.h"

#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

bool FARPGInputConfig::IsValid() const
{
	return InputTag.IsValid() && InputAction;
}

bool FARPGHeroAbilitySet::IsValid() const
{
	return AbilityToGrant && InputTag.IsValid();
}
