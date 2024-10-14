// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Types/ARPGMessagesStruct.h"
#include "Widget/ARPGWidgetBase.h"
#include "StatusBarWidget.generated.h"
class UCurveLinearColor;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ARPG_API UStatusBarWidget : public UARPGWidgetBase
{
	GENERATED_BODY()

	float MaxValue = {};
	float CurrentValue = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> ProgressBar_Main;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCurveLinearColor> StatusBarColor;

protected:
	UFUNCTION(BlueprintCallable, Category="ARPG|Widgets")
	virtual void SetMaxValue(float MaxValue);
	UFUNCTION(BlueprintCallable, Category="ARPG|Widgets")
	virtual void SetCurrentValue(float CurrentValue);
	UFUNCTION(BlueprintCallable, Category="ARPG|Widgets")
	virtual void RefreshProgressBar();

	void SetProgressbarColorBasedOnValues() const;
};
