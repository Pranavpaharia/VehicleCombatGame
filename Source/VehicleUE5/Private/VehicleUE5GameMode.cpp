// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleUE5GameMode.h"
#include "VehicleUE5Hud.h"
#include "VehiclePlayerState.h"
#include "VehicleGameState.h"
#include "VehicleGameSession.h"
#include "VehicleUE5GameInstance.h"
#include "OnlineBeaconHost.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
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

	UE_LOG(LogTemp, Warning, TEXT("Looking for Player Start for Newplayer"));

	

	
	

	//FActorSpawnParameters params;
	//AVehicleUE5Pawn* carPawn = GetWorld()->SpawnActor<AVehicleUE5Pawn>(CarPawnClass,actr->GetActorLocation(),actr->GetActorRotation(),params);
	//NewPlayer->Possess(carPawn);
}

void AVehicleUE5GameMode::SetMatchState(FName NewState)
{
	Super::SetMatchState(NewState);
	UE_LOG(LogTemp, Warning, TEXT("Set Match State to %s") , *NewState.ToString());
}

void AVehicleUE5GameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();
	UE_LOG(LogTemp, Warning, TEXT("OnMatchStateSet on GameMode!"));
}

void AVehicleUE5GameMode::NotifyPendingConnectionLost(const FUniqueNetIdRepl& ConnectionUniqueId)
{
	Super::NotifyPendingConnectionLost(ConnectionUniqueId);
	UE_LOG(LogTemp, Warning, TEXT("Connection lost in the middle  %s"), *ConnectionUniqueId.ToString());
}

void AVehicleUE5GameMode::HandleDisconnect(UWorld* InWorld, UNetDriver* NetDriver)
{
	Super::HandleDisconnect(InWorld, NetDriver);
	UE_LOG(LogTemp, Warning, TEXT("Handle Disconnected Player! %s"), *NetDriver->GetName());
}

void AVehicleUE5GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Post Login! Player controller: %s"), *NewPlayer->GetName());
	SendSessionIDToClient(NewPlayer);
	
}

void AVehicleUE5GameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	UE_LOG(LogTemp, Warning, TEXT("Player Logout! : %s"), *Exiting->GetName());
}

void AVehicleUE5GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogTemp, Warning, TEXT("InitGame Called On Server! MapName: %s "), *MapName);
}

void AVehicleUE5GameMode::StartPlay()
{
	Super::StartPlay();
	UE_LOG(LogTemp, Warning, TEXT("Start Play called on Gamemode!"));
}


void AVehicleUE5GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (sessionStringID.IsEmpty() && GetNetMode() == ENetMode::NM_DedicatedServer )
	{
		UVehicleUE5GameInstance* gInstance = Cast<UVehicleUE5GameInstance>(GetWorld()->GetGameInstance());
		if (gInstance)
		{
			FString sessionString;
			gInstance->GetCurrentSessionID_AsString(this, sessionString);
			UE_LOG(LogTemp, Warning, TEXT("Session id is:  %s"), *sessionString);
			if (!sessionString.IsEmpty())
				sessionStringID = sessionString;

		}
	}
	
}


void AVehicleUE5GameMode::SendSessionIDToClient(APlayerController* NewPlayer)
{
	check(NewPlayer)

	if (!NewPlayer)
		return;

	AVehiclePlayerState* pState = Cast<AVehiclePlayerState>(NewPlayer->PlayerState);

	if (pState)
	{
		pState->SetSessionIDString(sessionStringID);
		UE_LOG(LogTemp, Warning, TEXT("Session id %s sent to player with name:  %s"), *sessionStringID, *pState->GetCandidateName());
	}
}
