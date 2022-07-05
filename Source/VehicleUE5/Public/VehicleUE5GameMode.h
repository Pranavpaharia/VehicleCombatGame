// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VehicleBeaconHostObject.h"
#include "VehicleBeaconClient.h"
#include "VehicleUE5GameMode.generated.h"

UCLASS(MinimalAPI)
class AVehicleUE5GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AVehicleUE5GameMode();

	UFUNCTION()
	bool SpawnHostBeacon();

	UFUNCTION()
	bool SpawnClientBeacon();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	AVehicleBeaconHostObject* ServerBeacon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	AVehicleBeaconClient* ClientBeacon;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ConnectToDedicatedServer(const FString& address);



};



