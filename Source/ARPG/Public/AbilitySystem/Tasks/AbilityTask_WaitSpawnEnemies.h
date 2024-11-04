// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorSpawn, TArray<AActor*>, Actors);

class AARPGEnemyCharacter;
/**
 * 
 */
UCLASS()
class ARPG_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

protected:
	FGameplayTag CachedEventTag;


	TSoftClassPtr<AARPGEnemyCharacter> CachedEnemyToSpawn;

	int CachedHowMany;
	FVector CachedSpawnOrigin;
	float CachedMaxSpawnDistanceFromOrigin;
	FDelegateHandle DelegateHandle;

	void OnSpawnEvent(const FGameplayEventData* GameplayEventData);

	void Failed();

	void GeneratePoints(TArray<FVector>& PointsToGenerate);

public:
	virtual void Activate() override;
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta=(HidePin="Owner", DefaultToSelf="Owner", HowMany="1", MaxSpawnDistanceFromOrigin="200"))
	static UAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(
		UGameplayAbility* Owner,
		FGameplayTag EventTag,
		TSoftClassPtr<AARPGEnemyCharacter> EnemyToSpawn,
		int HowMany,
		FVector SpawnOrigin,
		float MaxSpawnDistanceFromOrigin);

	virtual void OnDestroy(bool bInOwnerFinished) override;

	FOnActorSpawn ActorSpawned;
	FOnActorSpawn ActorNotSpawned;
};
