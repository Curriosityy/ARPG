// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "DebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGHeroAttributeSet.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Input/ARPGInputComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "DTO/InputActionValueDTO.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameplayMessageSubsystem.h"

AARPGHeroCharacter::AARPGHeroCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer
	      .SetDefaultSubobjectClass<UHeroCombatComponent>(CombatComponentName)
	      .SetDefaultSubobjectClass<UARPGHeroAttributeSet>(AttributeSetName)
	      .SetDefaultSubobjectClass<UHeroUIComponent>(UIComponentName))
{
	GetCapsuleComponent()->SetCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = {0.f, 55.f, 65.f};
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = {500.f, 500.f, 500.f};
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AARPGHeroCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2d RotationVector = Value.Get<FVector2d>();

	if (RotationVector.X != 0.f)
	{
		AddControllerYawInput(RotationVector.X);
	}

	if (RotationVector.Y != 0.f)
	{
		AddControllerPitchInput(RotationVector.Y);
	}
}

void AARPGHeroCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2d movementVector = Value.Get<FVector2d>();
	const FRotator MovementRotator{0.f, Controller->GetControlRotation().Yaw, 0.f};

	if (movementVector.Y != 0.f)
	{
		AddMovementInput(MovementRotator.RotateVector(FVector::ForwardVector), movementVector.Y);
	}

	if (movementVector.X != 0.f)
	{
		AddMovementInput(MovementRotator.RotateVector(FVector::RightVector), movementVector.X);
	}
}

void AARPGHeroCharacter::Input_SwitchTarget(const FInputActionValue& Value)
{
	const int SwitchTagAbility = GetARPGAbilitySystemComponent()->
		GetActivatableAbilityIndexBasedOnDynamicTag(ARPGGameplayTags::InputTag_Toggle_TargetLock);
	check(SwitchTagAbility!=-1);

	auto AbilityToTrigger = GetARPGAbilitySystemComponent()->GetActivatableAbilities()[SwitchTagAbility];

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = this;
	auto DTO = NewObject<UInputActionValueDTO>();
	DTO->Value = Value;
	EventData.OptionalObject = DTO;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, ARPGGameplayTags::Player_Event_ChangeTarget,
	                                                         EventData);
}

void AARPGHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	GetARPGAbilitySystemComponent()->OnAbilityInputPressed(InInputTag);
}

void AARPGHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	GetARPGAbilitySystemComponent()->OnAbilityInputReleased(InInputTag);
}

void AARPGHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	if (CharacterStartupData.IsNull())
	{
		return;
	}

	UDataAsset_StartUpDataBase* loadedData = CharacterStartupData.LoadSynchronous();

	checkf(loadedData, TEXT("AARPGHeroCharacter::PossessedBy: Failed to load CharacterStartupData"));
	loadedData->GiveToAbilitySystemComponent(GetARPGAbilitySystemComponent(), 1);
}

void AARPGHeroCharacter::BeginPlay()
{
	auto subsystem = GetGameInstance()->GetSubsystem<UGameplayMessageSubsystem>();
	//subsystem->BroadcastMessage(FGameplayTag::EmptyTag, {});
	Super::BeginPlay();
}

void AARPGHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset is NULL"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UARPGInputComponent* ARPGInputComponent = CastChecked<UARPGInputComponent>(PlayerInputComponent);

	ARPGInputComponent->BindNativeInputAction(InputConfigDataAsset,
	                                          ARPGGameplayTags::InputTag_Look,
	                                          ETriggerEvent::Triggered,
	                                          this,
	                                          &ThisClass::Input_Look);

	ARPGInputComponent->BindNativeInputAction(InputConfigDataAsset,
	                                          ARPGGameplayTags::InputTag_Move,
	                                          ETriggerEvent::Triggered,
	                                          this,
	                                          &ThisClass::Input_Move);

	ARPGInputComponent->BindNativeInputAction(InputConfigDataAsset,
	                                          ARPGGameplayTags::InputTag_SwitchTarget,
	                                          ETriggerEvent::Triggered,
	                                          this,
	                                          &AARPGHeroCharacter::Input_SwitchTarget);

	ARPGInputComponent->BindAbilityInputAction(InputConfigDataAsset, this,
	                                           &ThisClass::Input_AbilityInputPressed,
	                                           &ThisClass::Input_AbilityInputReleased);
}
