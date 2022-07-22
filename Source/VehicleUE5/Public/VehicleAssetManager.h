// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "VehicleAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UVehicleAssetManager : public UAssetManager
{
	GENERATED_BODY()

	static UVehicleAssetManager& Get();

	virtual void StartInitialLoading() override;

	void InitializeAbilitySystem();

	UPROPERTY()
	TSet<const UObject*> LoadedAssets;

};
