// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Types/ARPGStructTypes.h"
#include "DataAsset_InputConfig.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FARPGInputConfig> NativeInputActions = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FARPGInputConfig> AbilityInputActions = {};

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
