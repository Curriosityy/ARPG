// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAttributeSet.h"

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "GameplayEffectExtension.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interfaces/UIComponentInterface.h"
#include "Net/UnrealNetwork.h"
#include "Types/ARPGMessagesStruct.h"

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

void UARPGAttributeSet::DealDamage(const FGameplayEffectModCallbackData& Data)
{
	const float OldHealth = {GetCurrentHealth()};
	const float NewHealth = {FMath::Clamp(OldHealth - GetDamageTaken(), 0, GetMaxHealth())};
	SetCurrentHealth(NewHealth);
	SetDamageTaken(0.f);

	if (NewHealth > 0)
	{
		return;
	}

	UARPGFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),
	                                                  ARPGGameplayTags::Shared_Status_Death);
}


void UARPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);


	if (!UIComponentInterface.IsValid())
	{
		UIComponentInterface = Cast<IUIComponentInterface>(Data.Target.GetAvatarActor());
	}

	checkf(UIComponentInterface.IsValid(), TEXT("%s didn't implement IUIComponentInterface"),
	       *Data.Target.GetAvatarActor()->GetName())

	checkf(UIComponentInterface->GetUIComponent(), TEXT("%s UIComponentInterface->GetUIComponent() return nullptr"),
	       *Data.Target.GetAvatarActor()->GetName())

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		DealDamage(Data);
	}
}

void UARPGAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	FGameplayTag BroadcastTag = {};

	if (Attribute == GetMaxHealthAttribute())
	{
		BroadcastTag = ARPGGameplayTags::Message_OnMaxHealthChanged;
	}

	if (Attribute == GetCurrentHealthAttribute())
	{
		BroadcastTag = ARPGGameplayTags::Message_OnHealthChanged;
	}

	if (BroadcastTag.IsValid())
	{
		UGameplayMessageSubsystem::Get(this).BroadcastMessage(BroadcastTag,
		                                                      FValueChanged{GetOwningActor(), OldValue, NewValue});
	}
}
