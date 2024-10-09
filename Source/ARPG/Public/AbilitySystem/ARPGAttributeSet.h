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
	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing = OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth = {};
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth = {};
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category="Rage", ReplicatedUsing = OnRep_CurrentRage)
	FGameplayAttributeData CurrentRage = {};
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CurrentRage);

	UPROPERTY(BlueprintReadOnly, Category="Rage", ReplicatedUsing = OnRep_MaxRage)
	FGameplayAttributeData MaxRage = {};
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxRage);

	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower = {};
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing = OnRep_DefencePower)
	FGameplayAttributeData DefencePower = {};
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, DefencePower);

	UARPGAttributeSet();

	UFUNCTION()
	void OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_CurrentRage(const FGameplayAttributeData& OldRage);
	UFUNCTION()
	void OnRep_MaxRage(const FGameplayAttributeData& OldRage);
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
	UFUNCTION()
	void OnRep_DefencePower(const FGameplayAttributeData& OldDefencePower);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
