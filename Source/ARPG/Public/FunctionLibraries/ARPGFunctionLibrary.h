// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARPGFunctionLibrary.generated.h"

class UARPGAbilitySystemComponent;

UENUM()
enum class EARPGConfirmType: uint8
{
	Yes,
	No
};

/**
 * 
 */
UCLASS()
class ARPG_API UARPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UARPGAbilitySystemComponent* NativeGetARPGASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* Actor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* Actor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary",
		meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* Actor, FGameplayTag Tag, EARPGConfirmType& OutConfirmType);
};
