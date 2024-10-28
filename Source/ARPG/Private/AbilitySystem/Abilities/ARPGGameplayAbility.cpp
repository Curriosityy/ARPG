// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Types/ARPGEnumTypes.h"

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

FGameplayEffectSpecHandle UARPGGameplayAbility::MakeEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
                                                                     TMap<FGameplayTag, float> EffectData) const
{
	checkf(Effect, TEXT("Effect in UARPGGameplayAbility::MakeEfectSpecHandle is NULLPTR"));

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(
		Effect,
		GetAbilityLevel(),
		ContextHandle
	);
	for (TTuple<FGameplayTag, float> Data : EffectData)
	{
		if (!Data.Key.IsValid() || EffectSpecHandle.Data->SetByCallerTagMagnitudes.Find(Data.Key))
		{
			continue;
		}

		EffectSpecHandle.Data->SetSetByCallerMagnitude(Data.Key, Data.Value);
	}

	return EffectSpecHandle;
}

TMap<FGameplayTag, float> UARPGGameplayAbility::MakeDamageSpecMap(const float BaseDamage,
                                                                  const FGameplayTag CurrentAttackTypeTag,
                                                                  const int CurrentComboCount,
                                                                  const bool ShouldHitReact)
{
	checkf(CurrentAttackTypeTag.IsValid(),
	       TEXT("UARPGGameplayAbility::MakeDamageSpecMap CurrentAttackTypeTag Need to be valid"))

	TMap<FGameplayTag, float> DamageSpecMap;
	DamageSpecMap.Add(ARPGGameplayTags::Shared_SetByCaller_BaseDamage, BaseDamage);
	DamageSpecMap.Add(CurrentAttackTypeTag, {});
	DamageSpecMap.Add(ARPGGameplayTags::Shared_SetByCaller_ComboCount, CurrentComboCount);

	if (ShouldHitReact)
	{
		DamageSpecMap.Add(ARPGGameplayTags::Shared_Event_HitReact, {});
	}

	return DamageSpecMap;
}

FActiveGameplayEffectHandle UARPGGameplayAbility::Native_ApplyEffectSpecHandle(AActor* TargetActor,
                                                                               const FGameplayEffectSpecHandle&
                                                                               InSpecHandle)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	checkf(ASC, TEXT("UARPGGameplayAbility::Native_ApplyEffectSpecHandle Target Actor has no ASC"));
	checkf(InSpecHandle.IsValid(), TEXT("UARPGGameplayAbility::Native_ApplyEffectSpecHandle InSpecHandle is invalid"));
	return GetAbilitySystemComponentFromActorInfo()
		->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, ASC);
}

FActiveGameplayEffectHandle UARPGGameplayAbility::BP_ApplyEffectSpecHandle(AActor* TargetActor,
                                                                           const FGameplayEffectSpecHandle&
                                                                           InSpecHandle, EARPGSuccessType& IsSpecValid)
{
	FActiveGameplayEffectHandle handle = Native_ApplyEffectSpecHandle(TargetActor, InSpecHandle);
	IsSpecValid = handle.WasSuccessfullyApplied() ? EARPGSuccessType::Successful : EARPGSuccessType::Unsuccessful;
	return handle;
}
