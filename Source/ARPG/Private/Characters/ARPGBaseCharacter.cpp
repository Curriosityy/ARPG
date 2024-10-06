// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGBaseCharacter.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AARPGBaseCharacter::AARPGBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>("AttributeSet");
}

void AARPGBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!AbilitySystemComponent)
		return;
	
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
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
