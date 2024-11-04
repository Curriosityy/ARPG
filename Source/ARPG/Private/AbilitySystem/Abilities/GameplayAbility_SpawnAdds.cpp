// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GameplayAbility_SpawnAdds.h"

#include "ARPGGameplayTags.h"
#include "AbilitySystem/Tasks/AbilityTask_WaitSpawnEnemies.h"

UGameplayAbility_SpawnAdds::UGameplayAbility_SpawnAdds()
{
	AbilityTags.AddTag(ARPGGameplayTags::Enemy_Ability_SpawnAdds);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_SpawnAdds::OnActorSpawned(TArray<AActor*> Actors)
{
	EndAbility(GetCurrentAbilitySpecHandle(),
	           GetCurrentActorInfo(),
	           GetCurrentActivationInfo(),
	           true,
	           false);
}

void UGameplayAbility_SpawnAdds::OnActorNotSpawned(TArray<AActor*> Actors)
{
	EndAbility(GetCurrentAbilitySpecHandle(),
	           GetCurrentActorInfo(),
	           GetCurrentActivationInfo(),
	           true,
	           false);
}

void UGameplayAbility_SpawnAdds::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_WaitSpawnEnemies* Task = UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(
		this,
		ARPGGameplayTags::Enemy_Event_Spawn,
		EnemyToSpawn,
		HowManyToSpawn,
		GetOwningActorFromActorInfo()->GetActorLocation(),
		SpawnDistance);

	Task->ActorSpawned.AddDynamic(this, &UGameplayAbility_SpawnAdds::OnActorSpawned);
	Task->ActorNotSpawned.AddDynamic(this, &UGameplayAbility_SpawnAdds::OnActorNotSpawned);
	Task->ReadyForActivation();
}

void UGameplayAbility_SpawnAdds::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
