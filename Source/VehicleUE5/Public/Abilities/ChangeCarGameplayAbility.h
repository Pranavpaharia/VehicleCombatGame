// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/VehicleGameplayAbility.h"
#include "ChangeCarGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UChangeCarGameplayAbility : public UVehicleGameplayAbility
{
	GENERATED_BODY()

	UChangeCarGameplayAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
