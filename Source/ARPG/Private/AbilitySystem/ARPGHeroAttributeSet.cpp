// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGHeroAttributeSet.h"

#include "Net/UnrealNetwork.h"

UARPGHeroAttributeSet::UARPGHeroAttributeSet()
{
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
}

void UARPGHeroAttributeSet::OnRep_CurrentRage(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CurrentRage, OldRage);
}

void UARPGHeroAttributeSet::OnRep_MaxRage(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxRage, OldRage);
}

void UARPGHeroAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CurrentRage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxRage, COND_None, REPNOTIFY_Always);
}
