// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/ARPGHeroAnimInstance.h"

#include "Characters/ARPGHeroCharacter.h"

void UARPGHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(OwningCharacter)
		OwningHeroCharacter = Cast<AARPGHeroCharacter>(OwningCharacter);
}

void UARPGHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(bHasAcceleration)
	{
		ElapsedIdleTime = 0;
		bShouldEnderRelaxState = false;
	}else
	{
		ElapsedIdleTime+=DeltaSeconds;
		bShouldEnderRelaxState = ElapsedIdleTime >= EnterRelaxedStateThreshold;
	}
}
