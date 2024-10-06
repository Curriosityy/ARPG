// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnExtensionComponentBase.generated.h"


class AController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARPG_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T>
	T* GetPawnOwnerChecked() const;

	template <class T>
	T* GetOwningControllerChecked() const;

	APawn* GetOwnerChecked() const
	{
		return GetPawnOwnerChecked<APawn>();
	}
};

template <class T>
T* UPawnExtensionComponentBase::GetPawnOwnerChecked() const
{
	static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,
	              "'T' Template parameter of GetOwnerChecked must be derived from APawn");
	return CastChecked<T>(GetOwner());
}

template <class T>
T* UPawnExtensionComponentBase::GetOwningControllerChecked() const
{
	static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
	              "'T' Template parameter of GetOwningComtroller must be derived from AController");

	return CastChecked<T>(GetOwnerChecked()->GetController());
}
