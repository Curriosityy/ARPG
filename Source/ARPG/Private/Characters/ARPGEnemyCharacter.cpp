// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGEnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "DebugHelper.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widget/ARPGWidgetBase.h"

AARPGEnemyCharacter::AARPGEnemyCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer
	.SetDefaultSubobjectClass<UEnemyCombatComponent>(CombatComponentName)
	.SetDefaultSubobjectClass<UEnemyUIComponent>(UIComponentName))
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

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(GetMesh());
}

void AARPGEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStatupData();
}

void AARPGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetComponent->GetUserWidgetObject())
	{
		UARPGWidgetBase* Base = Cast<UARPGWidgetBase>(WidgetComponent->GetUserWidgetObject());
		checkf(Base, TEXT("UserWidgetObject in WidgetComponent should be based on UARPGWidgetBase Actor name %s"),
		       *GetName())
		Base->SetOwningActor(this);
	}
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
