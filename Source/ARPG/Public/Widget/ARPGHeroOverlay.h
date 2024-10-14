// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ARPGWidgetBase.h"
#include "ARPGHeroOverlay.generated.h"

class UARPGIconWidget;
class UStatusBarWidget;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGHeroOverlay : public UARPGWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UStatusBarWidget> HealthBar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UStatusBarWidget> RageBar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UARPGIconWidget> WeaponIcon;

protected:
	virtual void SetOwningActor(AActor* InUIOwner) override;
};
