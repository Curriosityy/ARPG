// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ARPGWidgetBase.h"
#include "InWorldCharacterInfo.generated.h"

class UStatusBarWidget;
/**
 * 
 */
UCLASS(Abstract)
class ARPG_API UInWorldCharacterInfo : public UARPGWidgetBase
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UStatusBarWidget> HealthBarWidget;

public:
	virtual void SetOwningActor(AActor* InUIOwner) override;
};
