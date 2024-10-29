// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/ARPGMessagesStruct.h"
#include "Widget/ARPGWidgetBase.h"
#include "StatusBarWidget.generated.h"
class UCurveLinearColor;
class UProgressBar;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProgressBarChanged, UProgressBar*, progressBar,
                                             UStatusBarWidget*, instigator);

UCLASS()
class ARPG_API UStatusBarWidget : public UARPGWidgetBase
{
	GENERATED_BODY()

	float MaxValue = {1};
	float CurrentValue = {1};

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

public:
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category="ARPG|Widgets")
	FOnProgressBarChanged OnProgressBarChanged;

	UFUNCTION(BlueprintCallable, Category="ARPG|Widgets")
	float GetCurrentValue() const { return CurrentValue; }

	UFUNCTION(BlueprintCallable, Category="ARPG|Widgets")
	float GetMaxValue() const { return MaxValue; }
};
