// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BossHealthBar.h"

#include "Components/TextBlock.h"
#include "Widget/StatusBarWidget.h"

void UBossHealthBar::SetOwningActor(AActor* InUIOwner)
{
	Super::SetOwningActor(InUIOwner);
	BossHealthBar->SetOwningActor(InUIOwner);
	//TODO: Refactor, get more specific name (mb translated)
	EnemyName->SetText(FText::FromString(InUIOwner->GetActorLabel()));
}
