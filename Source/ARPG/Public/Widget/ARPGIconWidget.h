// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Widget/ARPGWidgetBase.h"
#include "ARPGIconWidget.generated.h"

class UImageVisibleOnSet;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGIconWidget : public UARPGWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImageVisibleOnSet> Icon = {};
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> PreviewTexture = {};

	UPROPERTY(EditDefaultsOnly, meta=(Categories="Message"))
	FGameplayTag ChangeImageMessage = {};

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetIconImage(const TSoftObjectPtr<UTexture2D> NewTexture);
};
