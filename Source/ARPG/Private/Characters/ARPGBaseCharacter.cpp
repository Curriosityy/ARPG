// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGBaseCharacter.h"
#include "DebugHelper.h"
#include "MotionWarpingComponent.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Components/ARPGMovementComponentBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Components/UI/PawnUIComponent.h"


FName AARPGBaseCharacter::CombatComponentName(TEXT("CombatComponent"));
FName AARPGBaseCharacter::AttributeSetName(TEXT("AttributeSet"));
FName AARPGBaseCharacter::UIComponentName(TEXT("UIComponent"));

void AARPGBaseCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GetAbilitySystemComponent()->GetOwnedGameplayTags();
}

// Sets default values
AARPGBaseCharacter::AARPGBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer
		.SetDefaultSubobjectClass<UARPGMovementComponentBase>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>(AttributeSetName);
	CombatComponent = CreateDefaultSubobject<UPawnCombatComponent>(CombatComponentName);
	UIComponent = CreateDefaultSubobject<UPawnUIComponent>(UIComponentName);
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
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

void AARPGBaseCharacter::HandleDeath_Implementation(const TSoftObjectPtr<UNiagaraSystem>& NiagaraSystemToPlay)
{
	if (IsValidChecked(this))
	{
		GetMesh()->bPauseAnims = true;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

UPawnUIComponent* AARPGBaseCharacter::GetUIComponent() const
{
	return UIComponent;
}

void AARPGBaseCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	checkf(Cast<IGenericTeamAgentInterface>(GetController()),
	       TEXT("Controller is not implementing an IGenericTeamAgentInterface %s"),
	       *GetName());
	Cast<IGenericTeamAgentInterface>(GetController())->SetGenericTeamId(TeamID);
}

FGenericTeamId AARPGBaseCharacter::GetGenericTeamId() const
{
	checkf(Cast<IGenericTeamAgentInterface>(GetController()),
	       TEXT("Controller is not implementing an IGenericTeamAgentInterface %s"),
	       *GetName());
	return Cast<IGenericTeamAgentInterface>(GetController())->GetGenericTeamId();
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
