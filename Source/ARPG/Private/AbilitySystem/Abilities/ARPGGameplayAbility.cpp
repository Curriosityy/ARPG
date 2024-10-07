// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UARPGGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (!ActorInfo)
	{
		return;
	}


	if (Policy == EARPGAbilityActivationPolicy::OnGiven && !Spec.IsActive())
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UARPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (!ActorInfo)
	{
		return;
	}


	if (Policy == EARPGAbilityActivationPolicy::OnGiven)
	{
		ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

UPawnCombatComponent* UARPGGameplayAbility::GetCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UARPGAbilitySystemComponent* UARPGGameplayAbility::GetARPGAbilitySystemComponentFromActorInfo() const
{
	return Cast<UARPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
