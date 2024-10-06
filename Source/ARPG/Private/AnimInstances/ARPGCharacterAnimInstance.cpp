// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGCharacterAnimInstance.h"

#include "Characters/ARPGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UARPGCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningCharacter = Cast<AARPGBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
		MovementComponent = OwningCharacter->GetCharacterMovement();
	
}

void UARPGCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(!OwningCharacter || !MovementComponent)
		return;

	Velocity = OwningCharacter->GetVelocity();
	GroundSpeed = Velocity.Size2D();

	bHasAcceleration = MovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}
