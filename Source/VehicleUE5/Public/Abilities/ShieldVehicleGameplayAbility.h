// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/VehicleGameplayAbility.h"
#include "ShieldVehicleGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UShieldVehicleGameplayAbility : public UVehicleGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UGameplayEffect> ShieldGameplayEffect;


	UShieldVehicleGameplayAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
};
