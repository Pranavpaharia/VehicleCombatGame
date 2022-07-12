// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleUE5GameMode.h"
#include "VehicleUE5Pawn.h"
#include "VehicleUE5Hud.h"
#include "VehiclePlayerController.h"
#include "VehiclePlayerState.h"
#include "VehicleGameState.h"
#include "VehicleGameSession.h"
#include "OnlineBeaconHost.h"
#include "GameFramework/SpectatorPawn.h"

AVehicleUE5GameMode::AVehicleUE5GameMode()
{
	//DefaultPawnClass = AVehicleUE5Pawn::StaticClass();
	//HUDClass = AVehicleUE5Hud::StaticClass();
	
	DefaultPawnClass = ASpectatorPawn::StaticClass();
	PlayerControllerClass = AVehiclePlayerController::StaticClass();
	PlayerStateClass = AVehiclePlayerState::StaticClass();
	GameStateClass = AVehicleGameState::StaticClass();
	GameSessionClass = AVehicleGameSession::StaticClass();

	ServerBeacon = nullptr;
	ClientBeacon = nullptr;
}

bool AVehicleUE5GameMode::SpawnHostBeacon()
{
	bool bStatus = false;
	AOnlineBeaconHost* HostBeacon = GetWorld()->SpawnActor<AOnlineBeaconHost>(AOnlineBeaconHost::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	
	if (HostBeacon->InitHost())
	{
		UE_LOG(LogTemp, Warning, TEXT("Host Beacon Initialized"));
		HostBeacon->PauseBeaconRequests(false);
		ServerBeacon = GetWorld()->SpawnActor<AVehicleBeaconHostObject>(AVehicleBeaconHostObject::StaticClass());
		if (ServerBeacon)
		{
			HostBeacon->RegisterHost(ServerBeacon);
			UE_LOG(LogTemp, Warning, TEXT("Registered Host Object to Server"));
			bStatus = true;
		}
	}

	
	return bStatus;
}

bool AVehicleUE5GameMode::SpawnClientBeacon()
{
	bool bStatus = false;

	ClientBeacon = GetWorld()->SpawnActor<AVehicleBeaconClient>(AVehicleBeaconClient::StaticClass());
	
	if (ClientBeacon)
		bStatus = true;


	return bStatus;
	
}

void AVehicleUE5GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() == ENetMode::NM_DedicatedServer && SpawnHostBeacon())
		UE_LOG(LogTemp, Warning, TEXT("Server Beacon Hosted On Dedicated Server"));

	if (GetNetMode() == ENetMode::NM_Standalone && SpawnClientBeacon())
	{
		UE_LOG(LogTemp, Warning, TEXT("Client Beacon Hosted On Standalone Game"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Client Beacon Unable To Spawn"));
	}
		

	

}

void AVehicleUE5GameMode::ConnectToDedicatedServer(const FString& address)
{
	if (ClientBeacon )
	{
		ClientBeacon->ConnectToServer(address);
		UE_LOG(LogTemp, Warning, TEXT("ClientBeacon->GetConnectionState(): %s"), ClientBeacon->GetConnectionState());
	}
	else
	{
		ClientBeacon = GetWorld()->SpawnActor<AVehicleBeaconClient>(AVehicleBeaconClient::StaticClass());
		ClientBeacon->SetOwner(GetWorld()->GetFirstPlayerController()->GetPawn());
		ClientBeacon->ConnectToServer(address);
		UE_LOG(LogTemp, Warning, TEXT("ClientBeacon->GetConnectionState(): %s"), ClientBeacon->GetConnectionState());
	}
}

void AVehicleUE5GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("ALudoProjectGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)"));

	AActor* actr = ChoosePlayerStart(NewPlayer);
	if (actr != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerStart Actor Found!"));
		FVector vec = (actr)->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Position of start actor found %s"), *vec.ToString());

	}

	//FActorSpawnParameters params;
	//ATP_VehiclePawn* carPawn = GetWorld()->SpawnActor<ATP_VehiclePawn>(VehiclePawnClass,actr->GetActorLocation(),actr->GetActorRotation(),params);
	//NewPlayer->Possess(carPawn);


}