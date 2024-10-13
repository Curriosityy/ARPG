// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ARPGWidgetBase.h"

#include "Interfaces/UIComponentInterface.h"
#include "UObject/WeakInterfacePtr.h"

void UARPGWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UARPGWidgetBase::SetOwningActor(AActor* InUIOwner)
{
	checkf(InUIOwner, TEXT("UARPGWidgetBase::SetOwningActor InUIOwner is nullptr"))
	UIComponent = Cast<IUIComponentInterface>(GetOwningPlayerPawn());
	checkf(UIComponent.IsValid(),
	       TEXT("UARPGWidgetBase::SetOwningActor InUIOwner %s not implementing IUIcomponentInterface"),
	       *InUIOwner->GetName());
	UIOwner = InUIOwner;
}
