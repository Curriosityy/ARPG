// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/WeakInterfacePtr.h"
#include "ARPGWidgetBase.generated.h"

/**
 * 
 */
class IUIComponentInterface;

UCLASS()
class ARPG_API UARPGWidgetBase : public UUserWidget
{
	GENERATED_BODY()

	TWeakInterfacePtr<IUIComponentInterface> UIComponent;
	TWeakObjectPtr<AActor> UIOwner;

public:
	virtual void NativeOnInitialized() override;
	UFUNCTION(BlueprintCallable)
	void SetOwningActor(AActor* InUIOwner);
};
