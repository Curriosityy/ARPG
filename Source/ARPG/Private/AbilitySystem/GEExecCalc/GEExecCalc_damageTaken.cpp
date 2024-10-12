// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_damageTaken.h"

#include "ARPGGameplayTags.h"
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

	RelevantAttributesToCapture.Add(GetDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackPowerDef);
}

void UGEExecCalc_damageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& owningSpec = ExecutionParams.GetOwningSpec();
	const FGameplayEffectContextHandle& handle = owningSpec.GetContext();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = owningSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = owningSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackPowerDef, EvaluateParams,
	                                                           SourceAttPower);

	float SourceDefPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefencePowerDef, EvaluateParams,
	                                                           SourceDefPower);

	float BaseDamage = owningSpec.GetSetByCallerMagnitude(ARPGGameplayTags::Shared_SetByCaller_BaseDamage);
	float ComboCount = owningSpec.GetSetByCallerMagnitude(ARPGGameplayTags::Shared_SetByCaller_ComboCount);

	// if (owningSpec.SetByCallerTagMagnitudes.Find(ARPGGameplayTags::Player_SetByCaller_AttackType_Light)
	// 	{
	// 		owningSpec.GetSetByCallerMagnitude(ARPGGameplayTags::Player_SetByCaller_AttackType_Light);
	// 	}
	// 	else
	// 	{
	// 	}
	//
	// float ComboCount = owningSpec.GetSetByCallerMagnitude(ARPGGameplayTags::Player_SetByCaller_AttackType_Heavy);
}
