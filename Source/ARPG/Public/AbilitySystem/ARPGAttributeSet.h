// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ARPGAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class ARPG_API UARPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing = OnRep_DamageTaken)
	FGameplayAttributeData DamageTaken = {};
	ATTRIBUTE_ACCESSORS(ThisClass, DamageTaken);

	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing = OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth = {};
	ATTRIBUTE_ACCESSORS(ThisClass, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth = {};
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower = {};
	ATTRIBUTE_ACCESSORS(ThisClass, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing = OnRep_DefencePower)
	FGameplayAttributeData DefencePower = {};
	ATTRIBUTE_ACCESSORS(ThisClass, DefencePower);

	UARPGAttributeSet();

	UFUNCTION()
	void OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
	UFUNCTION()
	void OnRep_DefencePower(const FGameplayAttributeData& OldDefencePower);

	UFUNCTION()
	void OnRep_DamageTaken(const FGameplayAttributeData& OldDamageTaken);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
