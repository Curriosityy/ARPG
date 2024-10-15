// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "ImageVisibleOnSet.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UImageVisibleOnSet : public UImage
{
	GENERATED_BODY()

public:
	virtual void SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize) override;
};
