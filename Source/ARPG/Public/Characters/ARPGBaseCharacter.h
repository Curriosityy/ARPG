// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatComponentInterface.h"
#include "Interfaces/Deathable.h"
#include "Interfaces/UIComponentInterface.h"
#include "ARPGBaseCharacter.generated.h"

class UMotionWarpingComponent;
class UPawnUIComponent;
class UPawnCombatComponent;
class UDataAsset_StartUpDataBase;
class UARPGAttributeSet;
class UARPGAbilitySystemComponent;
class UNiagaraSystem;

UCLASS()
class ARPG_API AARPGBaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatComponentInterface,
                                    public IDeathable, public IUIComponentInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TObjectPtr<UARPGAbilitySystemComponent> AbilitySystemComponent = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TObjectPtr<UARPGAttributeSet> AttributeSet = {};


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Combat")
	TObjectPtr<UPawnCombatComponent> CombatComponent = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="UI")
	TObjectPtr<UPawnUIComponent> UIComponent = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="MotionWarping")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent = {};

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
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() { return MotionWarpingComponent; };

	virtual
	FORCEINLINE UPawnCombatComponent* GetCombatComponent() const override { return CombatComponent; }

	static FName CombatComponentName;
	static FName AttributeSetName;
	static FName UIComponentName;

	UFUNCTION(BlueprintCallable)
	virtual void HandleDeath_Implementation(const TSoftObjectPtr<UNiagaraSystem>& NiagaraSystemToPlay) override;

	virtual UPawnUIComponent* GetUIComponent() const override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
};
