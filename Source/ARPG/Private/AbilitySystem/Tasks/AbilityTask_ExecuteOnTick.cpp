// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AbilityTask_ExecuteOnTick.h"

UAbilityTask_ExecuteOnTick::UAbilityTask_ExecuteOnTick()
{
	bTickingTask = true;
}

UAbilityTask_ExecuteOnTick* UAbilityTask_ExecuteOnTick::ExecuteOnTick(UGameplayAbility* OwningAbility)
{
	UAbilityTask_ExecuteOnTick* Task = NewAbilityTask<UAbilityTask_ExecuteOnTick>(OwningAbility);

	return Task;
}

void UAbilityTask_ExecuteOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (!ShouldBroadcastAbilityTaskDelegates())
	{
		EndTask();
		return;
	}

	OnTick.Broadcast(DeltaTime);
}
