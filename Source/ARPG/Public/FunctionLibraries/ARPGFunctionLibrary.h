// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/ARPGEnumTypes.h"
#include "ARPGFunctionLibrary.generated.h"

struct FScalableFloat;
class ICombatComponentInterface;
class UPawnCombatComponent;
class UARPGAbilitySystemComponent;


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

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary",
		meta = (DisplayName = "Get Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UPawnCombatComponent* GetCombatComponentFromActor(AActor* Actor, EARPGValidType& OutValidType);

	static UPawnCombatComponent* Native_GetCombatComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "ARPG|FunctionLibrary")
	static float GetScalableFloatValue(const FScalableFloat& InScalableFloat, const int Level);

	UFUNCTION(BlueprintPure, Category = "ARPG|FunctionLibrary")
	static EARPGHitDirection GetHitDirection(const AActor* Victim, const AActor* Attacker);
};
