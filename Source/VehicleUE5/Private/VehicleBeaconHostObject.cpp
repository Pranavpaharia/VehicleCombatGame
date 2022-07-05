// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBeaconHostObject.h"
#include "VehicleBeaconClient.h"

AVehicleBeaconHostObject::AVehicleBeaconHostObject()
{
	ClientBeaconActorClass = AVehicleBeaconClient::StaticClass();
	BeaconTypeName = ClientBeaconActorClass->GetName();
}

void AVehicleBeaconHostObject::OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection)
{
	Super::OnClientConnected(NewClientActor, ClientConnection);

	if (NewClientActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("New Beacon Client Connected! ID: %s"), *NewClientActor->GetBeaconType());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Connected Client Invalid!"));
	}
}

void AVehicleBeaconHostObject::NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor)
{
	Super::NotifyClientDisconnected(LeavingClientActor);
}