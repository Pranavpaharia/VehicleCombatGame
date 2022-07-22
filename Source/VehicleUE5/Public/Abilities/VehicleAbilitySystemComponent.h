// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "VehicleAbilitySystemComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceiveDamageDelegate, UVehicleAbilitySystemComponent*, sourceASC, float, UnmitigatedDamage, float, MitigatedDamage);
UCLASS()
class VEHICLEUE5_API UVehicleAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UVehicleAbilitySystemComponent();

	int32 GetDefaultAbilityLevel() const;

	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	static UVehicleAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

	void ReceiveDamage(UVehicleAbilitySystemComponent* SourceARC, float UnmitigatedDamage, float MitigatedDamage);

	FReceiveDamageDelegate OnReceiveDamage;
};
