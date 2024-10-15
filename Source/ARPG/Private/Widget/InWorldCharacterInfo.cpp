// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InWorldCharacterInfo.h"

#include "Widget/StatusBarWidget.h"

void UInWorldCharacterInfo::SetOwningActor(AActor* InUIOwner)
{
	Super::SetOwningActor(InUIOwner);
	HealthBarWidget->SetOwningActor(InUIOwner);
}
