// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleUE5/VehicleUE5.h"
#include "Abilities/GameplayAbility.h"
#include "VehicleGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UVehicleGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UVehicleGameplayAbility();

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Ability")
	EVehiclePowerAbilityID AbilityPowerInputID = EVehiclePowerAbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EVehiclePowerAbilityID AbilityPowerID = EVehiclePowerAbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
