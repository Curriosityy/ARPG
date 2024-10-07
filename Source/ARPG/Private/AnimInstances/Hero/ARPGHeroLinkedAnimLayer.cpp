// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/ARPGHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/ARPGHeroAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

UARPGHeroAnimInstance* UARPGHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UARPGHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
