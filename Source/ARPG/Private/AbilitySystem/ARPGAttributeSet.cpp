// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAttributeSet.h"

#include "Net/UnrealNetwork.h"

UARPGAttributeSet::UARPGAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);

	InitCurrentRage(1.f);
	InitMaxRage(1.f);

	InitAttackPower(1.f);
	InitDefencePower(1.f);
}

void UARPGAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CurrentHealth, OldHealth);
}

void UARPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxHealth, OldHealth);
}

void UARPGAttributeSet::OnRep_CurrentRage(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CurrentRage, OldRage);
}

void UARPGAttributeSet::OnRep_MaxRage(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxRage, OldRage);
}

void UARPGAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, AttackPower, OldAttackPower);
}

void UARPGAttributeSet::OnRep_DefencePower(const FGameplayAttributeData& OldDefencePower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, DefencePower, OldDefencePower);
}

void UARPGAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CurrentRage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxRage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, DefencePower, COND_None, REPNOTIFY_Always);
}
