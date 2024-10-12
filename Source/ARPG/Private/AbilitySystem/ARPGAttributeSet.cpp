// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UARPGAttributeSet::UARPGAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);

	InitAttackPower(1.f);
	InitDefencePower(1.f);
}

void UARPGAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CurrentHealth, OldHealth);
}

void UARPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldHealth);
}

void UARPGAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, AttackPower, OldAttackPower);
}

void UARPGAttributeSet::OnRep_DefencePower(const FGameplayAttributeData& OldDefencePower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, DefencePower, OldDefencePower);
}

void UARPGAttributeSet::OnRep_DamageTaken(const FGameplayAttributeData& OldDamageTaken)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, DamageTaken, OldDamageTaken);
}

void UARPGAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, DefencePower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, DamageTaken, COND_None, REPNOTIFY_Always);
}

void UARPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - GetDamageTaken(), 0, GetMaxHealth()));
		SetDamageTaken(0.f);

		//TODO:Notify UI
		//TODO:Kill if HP <=0
	}
}
