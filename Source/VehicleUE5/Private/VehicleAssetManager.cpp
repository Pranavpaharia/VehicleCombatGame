// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "Misc/ScopedSlowTask.h"
#include "Engine/Engine.h"
#include "Stats/StatsMisc.h"


UVehicleAssetManager& UVehicleAssetManager::Get()
{
	check(GEngine)

		if (UVehicleAssetManager* Singleton = Cast<UVehicleAssetManager>(GEngine->AssetManager))
		{
			return *Singleton;
		}


	UE_LOG(LogTemp, Warning, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini. It must be set to VehicleAssetManager!"));
	
	//Fatal Error above prevents this from being called.
	return *NewObject<UVehicleAssetManager>();
}

void UVehicleAssetManager::StartInitialLoading()
{
	// This does all of the scanning, need to do this now even if loads are deferred
	Super::StartInitialLoading();

	InitializeAbilitySystem();
}

void UVehicleAssetManager::InitializeAbilitySystem()
{
	UAbilitySystemGlobals::Get().InitGlobalData();
}
