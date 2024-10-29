// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ARPGWidgetBase.h"
#include "BossHealthBar.generated.h"

class UTextBlock;
class UStatusBarWidget;
/**
 * 
 */
UCLASS()
class ARPG_API UBossHealthBar : public UARPGWidgetBase
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UStatusBarWidget> BossHealthBar;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> EnemyName;
public:
	virtual void SetOwningActor(AActor* InUIOwner) override;
};
