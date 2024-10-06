// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "ARPGInputComponent.generated.h"


/**
 * 
 */
UCLASS()
class ARPG_API UARPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject,typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);
};

template <class UserObject, typename CallbackFunc>
inline void UARPGInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InputConfig,TEXT("Input config data asset is null"));

	UInputAction* InputAction = InputConfig->FindNativeInputActionByTag(InInputTag);

	if(!InputAction)
		return;

	BindAction(InputAction, TriggerEvent, ContextObject, Func);
	
}
