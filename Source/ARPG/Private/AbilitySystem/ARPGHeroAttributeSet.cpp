// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGHeroAttributeSet.h"

#include "ARPGGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interfaces/UIComponentInterface.h"
#include "Net/UnrealNetwork.h"
#include "Types/ARPGMessagesStruct.h"

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

void UARPGHeroAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		UGameplayMessageSubsystem& msg = UGameplayMessageSubsystem::Get(this);
		const float NewRage = FMath::Clamp(GetCurrentRage(), 0, GetMaxRage());
		const float OldRage = GetCurrentRage();

		SetCurrentRage(NewRage);
		msg.BroadcastMessage(ARPGGameplayTags::Message_OnRageChanged,
		                     FValueChanged{Data.Target.GetAvatarActor(), OldRage, NewRage});
	}
}

void UARPGHeroAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	FGameplayTag BroadcastTag = {};

	if (Attribute == GetMaxRageAttribute())
	{
		BroadcastTag = ARPGGameplayTags::Message_OnMaxRageChanged;
	}

	if (Attribute == GetCurrentRageAttribute())
	{
		BroadcastTag = ARPGGameplayTags::Message_OnRageChanged;
	}

	if (BroadcastTag.IsValid())
	{
		UGameplayMessageSubsystem::Get(this).BroadcastMessage(BroadcastTag,
		                                                      FValueChanged{GetOwningActor(), OldValue, NewValue});
	}
}
