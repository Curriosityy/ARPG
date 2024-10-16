// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGBaseAnimInstance.h"

#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "GameFramework/Pawn.h"

bool UARPGBaseAnimInstance::DoesOwnerHaveGameplayTag(const FGameplayTag Tag) const
{
	APawn* OwningPawn = TryGetPawnOwner();

	if (!OwningPawn)
	{
		return false;
	}

	return UARPGFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, Tag);
}
