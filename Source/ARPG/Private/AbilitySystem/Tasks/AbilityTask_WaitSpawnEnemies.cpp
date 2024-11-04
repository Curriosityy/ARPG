// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AbilityTask_WaitSpawnEnemies.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "Characters/ARPGEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UAbilityTask_WaitSpawnEnemies::OnSpawnEvent(const FGameplayEventData* GameplayEventData)
{
	if (CachedEnemyToSpawn.IsNull())
	{
		Failed();
		return;
	}


	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		CachedEnemyToSpawn.ToSoftObjectPath(),
		[&]()
		{
			TArray<AActor*> SpawnedActors{};
			UClass* EnemyAsset = CachedEnemyToSpawn.Get();

			if (!EnemyAsset)
			{
				Failed();
				return;
			}
			TArray<FVector> GeneratedPoints{};
			GeneratePoints(GeneratedPoints);
			FActorSpawnParameters params;

			for (const FVector& GeneratedPoint : GeneratedPoints)
			{
				FTransform spawnTransform = FTransform::Identity;
				spawnTransform.SetLocation(GeneratedPoint);
				spawnTransform.SetRotation(AbilitySystemComponent->GetAvatarActor()->GetActorRotation().Quaternion());
				AARPGEnemyCharacter* actor = GetWorld()->SpawnActorDeferred<AARPGEnemyCharacter>(
					EnemyAsset,
					spawnTransform,
					GetOwnerActor(),
					Cast<APawn>(GetOwnerActor()),
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
					ESpawnActorScaleMethod::OverrideRootScale
				);

				SpawnedActors.Add(actor);
			}

			for (AActor* actor : SpawnedActors)
			{
				actor->FinishSpawning(actor->GetTransform());
			}

			ActorSpawned.Broadcast(SpawnedActors);
		});
}

void UAbilityTask_WaitSpawnEnemies::Failed()
{
	ActorNotSpawned.Broadcast({});
	EndTask();
}

void UAbilityTask_WaitSpawnEnemies::GeneratePoints(TArray<FVector>& PointsToGenerate)
{
	//TODO SOME SMARTER WAY TO GENRATE POINTS

	for (int i = 0; i < CachedHowMany; i++)
	{
		FVector Point;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this,
		                                                        CachedSpawnOrigin,
		                                                        Point,
		                                                        CachedMaxSpawnDistanceFromOrigin
		);

		PointsToGenerate.Add(Point + FVector{0.f, 0, 100.f});
	}
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
	Super::Activate();
	DelegateHandle = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag).AddUObject(this,
		&ThisClass::OnSpawnEvent);
}

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* Owner,
                                                                               FGameplayTag EventTag,
                                                                               TSoftClassPtr<AARPGEnemyCharacter>
                                                                               EnemyToSpawn,
                                                                               int HowMany,
                                                                               FVector SpawnOrigin,
                                                                               float MaxSpawnDistanceFromOrigin)
{
	UAbilityTask_WaitSpawnEnemies* Task = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(Owner);

	Task->CachedEventTag = EventTag;
	Task->CachedEnemyToSpawn = EnemyToSpawn;
	Task->CachedHowMany = HowMany;
	Task->CachedSpawnOrigin = SpawnOrigin;
	Task->CachedMaxSpawnDistanceFromOrigin = MaxSpawnDistanceFromOrigin;


	return Task;
}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag).Remove(DelegateHandle);
	Super::OnDestroy(bInOwnerFinished);
}
