// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InWorldHealthBarWidget.h"

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "GameFramework/GameplayMessageSubsystem.h"

void UInWorldHealthBarWidget::SubscribeToMessage()
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);

	OnHealthChangedHandler = MessageSubsystem.RegisterListener(ARPGGameplayTags::Message_OnAttributeChanged,
	                                                           this,
	                                                           &UInWorldHealthBarWidget::OnHealthChanged);
}

void UInWorldHealthBarWidget::UnsubscribeFromMessage()
{
	if (IsValid(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(OnHealthChangedHandler);
	}
}

void UInWorldHealthBarWidget::OnHealthChanged(FGameplayTag Tag, const FOnHpChanged& OnHpChanged)
{
	if (IsSameAsOwningActor(OnHpChanged.Owner.Get()))
	{
		Debug::Print("UInWorldHealthBarWidget::OnHealthChanged");
	}
}
