// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHostObject.h"
#include "VehicleBeaconHostObject.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API AVehicleBeaconHostObject : public AOnlineBeaconHostObject
{
	GENERATED_BODY()

	AVehicleBeaconHostObject();

	virtual void OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection) override;

	virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor) override;
	
};
