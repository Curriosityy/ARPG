// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ImageVisibleOnSet.h"

void UImageVisibleOnSet::SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize)
{
	Super::SetBrushFromTexture(Texture, bMatchSize);
	SetVisibility(ESlateVisibility::Visible);
}
