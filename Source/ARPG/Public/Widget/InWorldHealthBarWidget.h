// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Types/ARPGMessagesStruct.h"
#include "Widget/ARPGWidgetBase.h"
#include "InWorldHealthBarWidget.generated.h"
/**
 * 
 */
UCLASS()
class ARPG_API UInWorldHealthBarWidget : public UARPGWidgetBase
{
	GENERATED_BODY()
	FGameplayMessageListenerHandle OnHealthChangedHandler = {};

protected:
	virtual void SubscribeToMessage() override;
	virtual void UnsubscribeFromMessage() override;
	void OnHealthChanged(FGameplayTag Tag, const FOnHpChanged& OnHpChanged);
};
