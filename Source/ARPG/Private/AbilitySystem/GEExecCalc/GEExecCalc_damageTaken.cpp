// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_damageTaken.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"
#include "DebugHelper.h"
#include "GameplayAbilityBlueprint.h"
#include "AbilitySystem/ARPGAttributeSet.h"

struct FARPGDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefencePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FARPGDamageCapture()
	{
		//DEFINE_ATTRIBUTE_CAPTUREDEF(Attribute set class, Property, Source/Targer,Snapshot (true/false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, DefencePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, DamageTaken, Target, false);
	}
};

static const FARPGDamageCapture& GetDamageCapture()
{
	static FARPGDamageCapture damageCapture = {};
	return damageCapture;
}

UGEExecCalc_damageTaken::UGEExecCalc_damageTaken()
{
	//Longer version
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
	RelevantAttributesToCapture.Add(GetDamageCapture().DefencePowerDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
}

void UGEExecCalc_damageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& OwningSpec = ExecutionParams.GetOwningSpec();
	const FGameplayEffectContextHandle& Handle = OwningSpec.GetContext();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = OwningSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = OwningSpec.CapturedTargetTags.GetAggregatedTags();

	float AttPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackPowerDef, EvaluateParams,
	                                                           AttPower);

	float DefPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefencePowerDef, EvaluateParams,
	                                                           DefPower);

	const float BaseDamage = OwningSpec.GetSetByCallerMagnitude(ARPGGameplayTags::Shared_SetByCaller_BaseDamage);
	const float ComboCount = OwningSpec.GetSetByCallerMagnitude(ARPGGameplayTags::Shared_SetByCaller_ComboCount);

	float DamageMultiplier = 1.0f;
	//TODO Multiplier should be injected by tag, not calculated like that (calculated in ability not here)
	if (OwningSpec.SetByCallerTagMagnitudes.Find(ARPGGameplayTags::Player_SetByCaller_AttackType_Light))
	{
		DamageMultiplier = (ComboCount - 1) * 0.05f + 1;
	}

	if (OwningSpec.SetByCallerTagMagnitudes.Find(ARPGGameplayTags::Player_SetByCaller_AttackType_Heavy))
	{
		DamageMultiplier = ComboCount * 0.15f + 1;
	}


	const float FinalDamage = BaseDamage * DamageMultiplier * AttPower / DefPower;

	if (OwningSpec.SetByCallerTagMagnitudes.Find(ARPGGameplayTags::Shared_Event_HitReact) && FinalDamage > 0)
	{
		FGameplayEventData payload;
		payload.Instigator = OwningSpec.GetEffectContext().GetInstigator();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor(),
			ARPGGameplayTags::Shared_Event_HitReact,
			payload);
	}

	OutExecutionOutput.AddOutputModifier(
		{GetDamageCapture().DamageTakenProperty, EGameplayModOp::Additive, FinalDamage});
}
