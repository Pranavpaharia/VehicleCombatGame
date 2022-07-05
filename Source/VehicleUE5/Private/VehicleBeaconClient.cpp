// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBeaconClient.h"


AVehicleBeaconClient::AVehicleBeaconClient()
{
	isConnected = false;
}

bool AVehicleBeaconClient::ConnectToServer(const FString& address)
{
	FURL destinationURL = FURL(nullptr, *address, ETravelType::TRAVEL_Absolute);
	destinationURL.Port = 7787;

	return InitClient(destinationURL);
}

void AVehicleBeaconClient::OnFailure()
{
	Super::OnFailure();
	UE_LOG(LogTemp, Warning, TEXT("Client failed to connect to host beacon"));
}

void AVehicleBeaconClient::OnConnected()
{
	Super::OnConnected();
	UE_LOG(LogTemp, Warning, TEXT("Client Connected to host beacon!"));
	isConnected = true;
}

void AVehicleBeaconClient::CheckPeopleOnServer_Implementation()
{
	
}