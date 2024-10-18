// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "ARPGGameplayTags.h"

UHeroGameplayAbility_TargetLock::UHeroGameplayAbility_TargetLock()
{
	AbilityTags.AddTag(ARPGGameplayTags::Player_Ability_TargetLock);

	ActivationOwnedTags.AddTag(ARPGGameplayTags::Player_Status_TargetLock);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//bRetriggerInstancedAbility = true;
}

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo,
                                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
