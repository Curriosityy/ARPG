// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ARPGGameplayAbility.generated.h"

enum class EARPGValidType : uint8;
class UARPGAbilitySystemComponent;
class UPawnCombatComponent;

UENUM()
enum class EARPGAbilityActivationPolicy : uint8
{
	OnTrigger,
	OnGiven,
};

/**
 * 
 */
UCLASS()
class ARPG_API UARPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="ARPG|Ability")
	EARPGAbilityActivationPolicy Policy = EARPGAbilityActivationPolicy::OnTrigger;

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
	                        const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo,
	                        bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UFUNCTION(BlueprintPure, Category="ARPG|Ability")
	UPawnCombatComponent* GetCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="ARPG|Ability")
	UARPGAbilitySystemComponent* GetARPGAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	FGameplayEffectSpecHandle MakeEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	                                               TMap<FGameplayTag, float> EffectData);

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	static TMap<FGameplayTag, float> MakeDamageSpecMap(float BaseDamage, FGameplayTag CurrentAttackTypeTag,
	                                                   int CurrentComboCount);

	FActiveGameplayEffectHandle Native_ApplyEffectSpecHandle(AActor* TargetActor,
	                                                         const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability",
		meta = (DisplayName = "Apply Effect Spec Handle to target", ExpandEnumAsExecs="Success"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandle(AActor* TargetActor,
	                                                     const FGameplayEffectSpecHandle& InSpecHandle,
	                                                     EARPGSuccessType& Success);
};
