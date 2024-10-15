// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ARPGIconWidget.h"

#include "Components/Image.h"
#include "Engine/AssetManager.h"
#include "Engine/Texture2D.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Widget/ImageVisibleOnSet.h"

void UARPGIconWidget::SetIconImage(const TSoftObjectPtr<UTexture2D> NewTexture)
{
	if (!NewTexture.IsPending() && !NewTexture.IsValid())
	{
		Icon->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	Icon->SetBrushFromSoftTexture(NewTexture, true);
}

void UARPGIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();


	SetIconImage(IsDesignTime() ? PreviewTexture : nullptr);
}
