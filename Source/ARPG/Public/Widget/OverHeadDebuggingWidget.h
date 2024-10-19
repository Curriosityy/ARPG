// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadDebuggingWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class ARPG_API UOverHeadDebuggingWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> DebugMessage;

public:
	void SetMessage(const FString& Msg);
};
