#pragma once
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "ARPGMessagesStruct.generated.h"
class AActor;

USTRUCT(BlueprintType)
struct ARPG_API FMessageBase
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct ARPG_API FOnDeath : public FMessageBase
{
	GENERATED_BODY()

	FOnDeath() = default;

	FOnDeath(AActor* InActor): Actor(InActor)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> Actor = {};
};

USTRUCT(BlueprintType)
struct ARPG_API FOnHpChanged : public FMessageBase
{
	GENERATED_BODY()
	FOnHpChanged() = default;

	FOnHpChanged(AActor* InActor, const float InOldHp, const float InNewHp): Owner(InActor), OldHp(InOldHp),
	                                                                         NewHp(InNewHp)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> Owner = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float OldHp = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NewHp = {};
};
