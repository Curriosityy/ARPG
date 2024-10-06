// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
{
	for (FARPGInputConfig& action : NativeInputActions)
	{
		if(action.InputTag == InInputTag)
		{
			return action.InputAction;
		}
	}
	
	return nullptr;
}
