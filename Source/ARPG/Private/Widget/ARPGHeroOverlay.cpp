// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ARPGHeroOverlay.h"

#include "Widget/ARPGIconWidget.h"
#include "Widget/StatusBarWidget.h"

void UARPGHeroOverlay::SetOwningActor(AActor* InUIOwner)
{
	Super::SetOwningActor(InUIOwner);
	HealthBar->SetOwningActor(InUIOwner);
	RageBar->SetOwningActor(InUIOwner);
	WeaponIcon->SetOwningActor(InUIOwner);
}
