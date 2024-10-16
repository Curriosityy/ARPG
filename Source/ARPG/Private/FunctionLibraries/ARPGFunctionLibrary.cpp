// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ARPGFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Interfaces/CombatComponentInterface.h"

UARPGAbilitySystemComponent* UARPGFunctionLibrary::NativeGetARPGASCFromActor(AActor* InActor)
{
	checkf(InActor, TEXT("UARPGFunctionLibrary::NativeGetARPGASCFromActor Actor is null"));

	return CastChecked<UARPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UARPGFunctionLibrary::AddGameplayTagToActorIfNone(AActor* Actor, FGameplayTag TagToAdd)
{
	UARPGAbilitySystemComponent* asc = NativeGetARPGASCFromActor(Actor);

	if (NativeDoesActorHaveTag(Actor, TagToAdd))
	{
		return;
	}

	asc->AddLooseGameplayTag(TagToAdd);
}

void UARPGFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* Actor, FGameplayTag TagToRemove)
{
	UARPGAbilitySystemComponent* asc = NativeGetARPGASCFromActor(Actor);

	if (!NativeDoesActorHaveTag(Actor, TagToRemove))
	{
		return;
	}

	asc->RemoveLooseGameplayTag(TagToRemove);
}

bool UARPGFunctionLibrary::NativeDoesActorHaveTag(AActor* Actor, FGameplayTag Tag)
{
	UARPGAbilitySystemComponent* asc = NativeGetARPGASCFromActor(Actor);
	return asc->HasMatchingGameplayTag(Tag);
}

void UARPGFunctionLibrary::BP_DoesActorHaveTag(AActor* Actor, FGameplayTag Tag, EARPGConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(Actor, Tag) == true ? EARPGConfirmType::Yes : EARPGConfirmType::No;
}

UPawnCombatComponent* UARPGFunctionLibrary::GetCombatComponentFromActor(AActor* Actor, EARPGValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = Native_GetCombatComponentFromActor(Actor);

	OutValidType = CombatComponent ? EARPGValidType::Valid : EARPGValidType::Invalid;

	return CombatComponent;
}

UPawnCombatComponent* UARPGFunctionLibrary::Native_GetCombatComponentFromActor(AActor* Actor)
{
	checkf(Actor, TEXT("UARPGFunctionLibrary::Native_GetCombatComponentFromActor Actor is NULL"));

	if (Actor->Implements<UCombatComponentInterface>())
	{
		return Cast<ICombatComponentInterface>(Actor)->GetCombatComponent();
	}

	return nullptr;
}

float UARPGFunctionLibrary::GetScalableFloatValue(const FScalableFloat& InScalableFloat, const int Level)
{
	return InScalableFloat.GetValueAtLevel(Level);
}
