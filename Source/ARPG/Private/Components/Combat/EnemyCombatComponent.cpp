// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"

void UEnemyCombatComponent::OnWeaponHit(AActor* ActorHitted, AActor* HittedBy)
{
	bool bIsPlayerBlocking = UARPGFunctionLibrary::NativeDoesActorHaveTag(
		ActorHitted, ARPGGameplayTags::Player_Status_Blocking);
	bool bIsBlockValid = false;
	if (bIsPlayerBlocking)
	{
		bIsBlockValid = UARPGFunctionLibrary::GetHitDirection(ActorHitted, HittedBy, 60) == EARPGHitDirection::Front;
	}

	if (!bIsBlockValid)
	{
		Super::OnWeaponHit(ActorHitted, HittedBy);
	}

	FGameplayEventData data;
	data.Instigator = GetOwner();
	data.Target = ActorHitted;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorHitted,
	                                                         ARPGGameplayTags::Player_Event_SuccessfulBlock,
	                                                         data);
}
