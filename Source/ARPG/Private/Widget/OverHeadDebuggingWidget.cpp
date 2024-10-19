// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OverHeadDebuggingWidget.h"

#include "Components/TextBlock.h"

void UOverHeadDebuggingWidget::SetMessage(const FString& Msg)
{
	DebugMessage->SetText(FText::FromString(Msg));
}
