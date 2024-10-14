// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ARPGWidgetBase.h"

#include "DebugHelper.h"
#include "Interfaces/UIComponentInterface.h"
#include "UObject/WeakInterfacePtr.h"

void UARPGWidgetBase::SubscribeToMessage_Implementation()
{
	Debug::Print(FString::Printf(TEXT("SubscribeToMessage_Implementation is not implemented in %s"), *GetName()));
}

void UARPGWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SubscribeToMessage();
}

void UARPGWidgetBase::SetOwningActor(AActor* InUIOwner)
{
	checkf(InUIOwner, TEXT("UARPGWidgetBase::SetOwningActor InUIOwner is nullptr"))
	UIOwner = MakeWeakObjectPtr(InUIOwner);
	checkf(UIOwner.IsValid(), TEXT("UARPGWidgetBase::SetOwningActor UIOwner is nullptr"))
}

void UARPGWidgetBase::BeginDestroy()
{
	Super::BeginDestroy();
	//UnsubscribeFromMessage();
}

bool UARPGWidgetBase::IsSameAsOwningActor(const AActor* InActor) const
{
	return UIOwner.Get() == InActor;
}
