// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/VehicleGameplayAbility.h"
#include "VehicleHandBrakeGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UVehicleHandBrakeGameplayAbility : public UVehicleGameplayAbility
{
	GENERATED_BODY()

	UVehicleHandBrakeGameplayAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
