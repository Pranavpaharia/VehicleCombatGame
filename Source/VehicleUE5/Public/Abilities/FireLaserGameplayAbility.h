// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/VehicleGameplayAbility.h"
#include "Weapons/LaserProjectile.h"
#include "FireLaserGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UFireLaserGameplayAbility : public UVehicleGameplayAbility
{
	GENERATED_BODY()

public:
	UFireLaserGameplayAbility();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<ALaserProjectile> LaserProjectileClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData);


	
};
