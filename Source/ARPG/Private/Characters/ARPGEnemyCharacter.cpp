// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "DebugHelper.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AARPGEnemyCharacter::AARPGEnemyCharacter(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UEnemyCombatComponent>(CombatComponentName))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = {0.f, 180.f, 0.f};
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
}

void AARPGEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStatupData();
}

void AARPGEnemyCharacter::InitEnemyStatupData()
{
	if (CharacterStartupData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		[this]()
		{
			auto loadedData = CharacterStartupData.Get();
			if (!loadedData)
			{
				return;
			}

			loadedData->GiveToAbilitySystemComponent(GetARPGAbilitySystemComponent());
			Debug::Print("Enemy start up data loaded");
		});
}