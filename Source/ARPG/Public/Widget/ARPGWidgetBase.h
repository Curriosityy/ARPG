// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/WeakInterfacePtr.h"
#include "ARPGWidgetBase.generated.h"

struct FOnDeath;
/**
 * 
 */
class IUIComponentInterface;
//TODO: Move SubscribeToMessage UnsubscribeFromMessage to child? not every ARPG widget will subscribe to messages?
UCLASS()
class ARPG_API UARPGWidgetBase : public UUserWidget
{
	GENERATED_BODY()

	TWeakInterfacePtr<IUIComponentInterface> UIComponent;
	TWeakObjectPtr<AActor> UIOwner;

protected:
	virtual void SubscribeToMessage() PURE_VIRTUAL();
	virtual void UnsubscribeFromMessage() PURE_VIRTUAL();

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetOwningActor(AActor* InUIOwner);

	virtual void BeginDestroy() override;

	bool IsSameAsOwningActor(const AActor* InActor) const;
};
