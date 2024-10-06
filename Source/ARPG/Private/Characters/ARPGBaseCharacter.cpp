// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGBaseCharacter.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Combat/PawnCombatComponent.h"


FName AARPGBaseCharacter::CombatComponentName(TEXT("CombatComponent"));

// Sets default values
AARPGBaseCharacter::AARPGBaseCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>("AttributeSet");

	CombatComponent = CreateDefaultSubobject<UPawnCombatComponent>(CombatComponentName);
}

void AARPGBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);


	ensureMsgf(!CharacterStartupData.IsNull(), TEXT("Character Startup Data is not assigned in %s"), *GetName());
}

UARPGAbilitySystemComponent* AARPGBaseCharacter::GetARPGAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UARPGAttributeSet* AARPGBaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

UAbilitySystemComponent* AARPGBaseCharacter::GetAbilitySystemComponent() const
{
	return GetARPGAbilitySystemComponent();
}
