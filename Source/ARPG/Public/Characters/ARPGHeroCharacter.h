// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ARPGBaseCharacter.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "ARPGHeroCharacter.generated.h"

class UHeroCombatComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroCharacter : public AARPGBaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> CameraBoom = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> FollowCamera = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset = {};

public:
	AARPGHeroCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void Input_Look(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Move(const FInputActionValue& Value);

	UFUNCTION()
	void Input_SwitchTarget(const FInputActionValue& Value);

	UFUNCTION()
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	UFUNCTION()
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

	virtual void PossessedBy(AController* NewController) override;

	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const
	{
		return Cast<UHeroCombatComponent>(GetCombatComponent());
	}

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
