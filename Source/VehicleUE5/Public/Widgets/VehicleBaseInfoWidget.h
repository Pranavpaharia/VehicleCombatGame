// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleBaseInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UVehicleBaseInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthBar(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetNitroManaBar(float NitroPercentage);

	

};
