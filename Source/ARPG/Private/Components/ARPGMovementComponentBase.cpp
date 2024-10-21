// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGMovementComponentBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"

UARPGMovementComponentBase::UARPGMovementComponentBase()
{
}

float UARPGMovementComponentBase::GetMaxSpeed() const
{
	//if(UARPGFunctionLibrary::NativeDoesActorHaveTag(GetOwner(),STUN))
	//VALID WAY TO HANDLE STUN

	float maxSpeed = Super::GetMaxSpeed();

	switch (MovementMode)
	{
	case MOVE_Walking:
	case MOVE_NavWalking:

		maxSpeed = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent()->GetNumericAttribute(
			UARPGAttributeSet::GetMovementSpeedAttribute());

		break;
	default:
		break;
	}

	return maxSpeed;
}
