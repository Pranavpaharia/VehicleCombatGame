// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"
#include "VehicleBeaconClient.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API AVehicleBeaconClient : public AOnlineBeaconClient
{
	GENERATED_BODY()

	AVehicleBeaconClient();
	
	virtual void OnFailure() override;

	virtual void OnConnected() override;

public:
	UFUNCTION(BlueprintCallable)
	bool ConnectToServer(const FString& address);

	bool isConnected;

	UFUNCTION(Server,Reliable)
	void CheckPeopleOnServer();

};
