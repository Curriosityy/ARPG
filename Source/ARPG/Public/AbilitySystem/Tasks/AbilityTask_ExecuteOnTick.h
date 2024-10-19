// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteOnTick.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskTick, float, DeltaTime);

UCLASS()
class ARPG_API UAbilityTask_ExecuteOnTick : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnTaskTick OnTick{};

	UAbilityTask_ExecuteOnTick();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_ExecuteOnTick* ExecuteOnTick(UGameplayAbility* OwningAbility);

	virtual void TickTask(float DeltaTime) override;
};
