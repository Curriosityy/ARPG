// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGHeroCharacter.h"

#include "ARPGGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "DebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/Input/ARPGInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"

AARPGHeroCharacter::AARPGHeroCharacter(const FObjectInitializer& ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleSize(42.f,96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = {0.f,55.f,65.f};
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = {500.f,500.f,500.f};
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AARPGHeroCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2d RotationVector = Value.Get<FVector2d>();

	if(RotationVector.X != 0.f)
	{
		AddControllerYawInput(RotationVector.X);
	}

	if(RotationVector.Y != 0.f)
	{
		AddControllerPitchInput(RotationVector.Y);
	}
}

void AARPGHeroCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2d movementVector = Value.Get<FVector2d>();
	const FRotator MovementRotator {0.f,Controller->GetControlRotation().Yaw,0.f};

	if(movementVector.Y != 0.f)
	{
		AddMovementInput(MovementRotator.RotateVector(FVector::ForwardVector),movementVector.Y);
	}

	if(movementVector.X != 0.f)
	{
		AddMovementInput(MovementRotator.RotateVector(FVector::RightVector), movementVector.X);
	}
}

void AARPGHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(GetARPGAbilitySystemComponent() && GetAttributeSet())
	{
		const FString output = FString::Printf(TEXT("OwnerActor: %ls, Avatar actor: %ls"),
			*GetARPGAbilitySystemComponent()->GetOwnerActor()->GetActorLabel(),
			*GetARPGAbilitySystemComponent()->GetAvatarActor()->GetActorLabel());
		Debug::Print(TEXT("Ability system component and attribute set are valid. ") + output);
	}
}

void AARPGHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AARPGHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset is NULL"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

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
}