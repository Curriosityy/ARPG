// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StatusBarWidget.h"

#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"
#include "GameFramework/GameplayMessageSubsystem.h"


void UStatusBarWidget::SetMaxValue(float InMaxValue)
{
	MaxValue = InMaxValue;
}

void UStatusBarWidget::SetCurrentValue(float InCurrentValue)
{
	CurrentValue = InCurrentValue;
}

void UStatusBarWidget::RefreshProgressBar()
{
	ProgressBar_Main->SetPercent(CurrentValue / MaxValue);
	SetProgressbarColorBasedOnValues();
}

void UStatusBarWidget::SetProgressbarColorBasedOnValues() const
{
	ProgressBar_Main->SetFillColorAndOpacity(StatusBarColor->GetLinearColorValue(ProgressBar_Main->GetPercent()));
}