// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "ARPGBaseCharacter.generated.h"

class UPawnCombatComponent;
class UDataAsset_StartUpDataBase;
class UARPGAttributeSet;
class UARPGAbilitySystemComponent;

UCLASS()
class ARPG_API AARPGBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TObjectPtr<UARPGAbilitySystemComponent> AbilitySystemComponent = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TObjectPtr<UARPGAttributeSet> AttributeSet = {};


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Combat")
	TObjectPtr<UPawnCombatComponent> CombatComponent = {};

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartupData = {};

public:
	AARPGBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UARPGAbilitySystemComponent* GetARPGAbilitySystemComponent() const;
	UARPGAttributeSet* GetAttributeSet() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Sets default values for this character's properties
	virtual void PossessedBy(AController* NewController) override;

	FORCEINLINE UPawnCombatComponent* GetCombatComponent() const { return CombatComponent; }

	static FName CombatComponentName;
	static FName AttributeSetName;
};
