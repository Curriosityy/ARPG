// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_damageTaken.h"

#include "AbilitySystem/ARPGAttributeSet.h"

struct FARPGDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefencePower)

	FARPGDamageCapture()
	{
		//DEFINE_ATTRIBUTE_CAPTUREDEF(Attribute set class, Property, Source/Targer,Snapshot (true/false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, DefencePower, Target, false);
	}
};

static const FARPGDamageCapture& GetDamageCapture()
{
	static FARPGDamageCapture damageCapture = {};
	return damageCapture;
}

UGEExecCalc_damageTaken::UGEExecCalc_damageTaken()
{
	// FGameplayEffectAttributeCaptureDefinition AttackPowerDef =
	// {
	// 	FindFieldChecked<FProperty>(UARPGAttributeSet::StaticClass(),
	// 	                            GET_MEMBER_NAME_CHECKED(UARPGAttributeSet, AttackPower)),
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// };
	//
	// RelevantAttributesToCapture.Add(AttackPowerDef);
	FARPGDamageCapture capture = GetDamageCapture();
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(capture.AttackPowerDef);
}
