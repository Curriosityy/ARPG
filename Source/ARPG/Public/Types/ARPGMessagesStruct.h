#pragma once
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Items/Weapons/ARPGWeaponBase.h"
#include "ARPGMessagesStruct.generated.h"


USTRUCT(BlueprintType)
struct ARPG_API FMessageBase
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct ARPG_API FDeath : public FMessageBase
{
	GENERATED_BODY()

	FDeath() = default;

	FDeath(AActor* InActor): Actor(InActor)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> Actor = {};
};

USTRUCT(BlueprintType)
struct ARPG_API FValueChanged : public FMessageBase
{
	GENERATED_BODY()
	FValueChanged() = default;

	FValueChanged(AActor* InActor, const float InOldValue, const float InNewValue): Owner(InActor),
		OldValue(InOldValue),
		NewValue(InNewValue)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> Owner = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float OldValue = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NewValue = {};
};

USTRUCT(BlueprintType)
struct ARPG_API FWeaponChanged
{
	GENERATED_BODY()
	FWeaponChanged() = default;

	FWeaponChanged(AActor* InActor, AARPGWeaponBase* InNewWeapon): Owner(InActor),
	                                                               NewWeapon(InNewWeapon)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> Owner = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AARPGWeaponBase> NewWeapon = {};
};
