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

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;


	
};
