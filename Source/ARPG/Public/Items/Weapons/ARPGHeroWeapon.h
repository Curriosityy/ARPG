// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Items/Weapons/ARPGWeaponBase.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroWeapon : public AARPGWeaponBase
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities = {};

public:
	UFUNCTION(BlueprintCallable)
	void SetGrantedAbilities(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilities);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilities() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FARPGHeroWeaponData HeroWeaponData;

	virtual void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult) override;
};
