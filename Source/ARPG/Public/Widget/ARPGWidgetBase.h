// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/WeakInterfacePtr.h"
#include "ARPGWidgetBase.generated.h"

struct FDeath;
/**
 * 
 */
class IUIComponentInterface;
//TODO: Move SubscribeToMessage UnsubscribeFromMessage to child? not every ARPG widget will subscribe to messages?
UCLASS()
class ARPG_API UARPGWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TWeakObjectPtr<AActor> UIOwner = {};

	UFUNCTION(BlueprintNativeEvent)
	void SubscribeToMessage();

	virtual void SubscribeToMessage_Implementation();

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category="ARPG|Widgets")
	virtual void SetOwningActor(AActor* InUIOwner);

	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintPure, Category="ARPG|Widgets")
	bool IsSameAsOwningActor(const AActor* InActor) const;
};
