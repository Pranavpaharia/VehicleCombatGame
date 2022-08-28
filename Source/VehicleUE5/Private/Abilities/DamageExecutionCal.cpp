// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DamageExecutionCal.h"
#include "Abilities/VehicleAbilitySystemComponent.h"
#include "Abilities/VehicleAttributeSet.h"

struct FDamageStatistics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);


	FDamageStatistics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UVehicleAttributeSet, Damage, Source, true);
	}
};

static const FDamageStatistics& DamageStatistics()
{
	static FDamageStatistics DStats;
	return DStats;
}

UDamageExecutionCal::UDamageExecutionCal()
{
	RelevantAttributesToCapture.Add(DamageStatistics().DamageDef);
}

void UDamageExecutionCal::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.0f;
	// Capture optional damage value set on the damage GE as a CalculationModifier under the ExecutionCalculation
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatistics().DamageDef, EvaluationParameters, Damage);
	// Add SetByCaller damage if it exists
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	if (Damage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatistics().DamageProperty,EGameplayModOp::Additive,Damage));
	}

	// Broadcast damages to Target ASC
	UVehicleAbilitySystemComponent* TargetASC = Cast<UVehicleAbilitySystemComponent>(TargetAbilitySystemComponent);
	if (TargetASC)
	{
		UVehicleAbilitySystemComponent* SourceASC = Cast<UVehicleAbilitySystemComponent>(SourceAbilitySystemComponent);
		TargetASC->ReceiveDamage(SourceASC, Damage, Damage);
	}
}
