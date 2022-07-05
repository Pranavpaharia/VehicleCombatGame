// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePlayerController.h"
#include "OnlineSubsystemUtils.h"
#include "VehicleUE5GameMode.h"
#include "VehicleUE5Pawn.h"
#include "VehicleUE5GameInstance.h"


AVehiclePlayerController::AVehiclePlayerController()
{
	bCameraMove = false;
}

void AVehiclePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//DisableInput(this);

	//Show widget based on single player or multiplayer
	//Check for Connected Client and Standalone version


	if (GetNetMode() == ENetMode::NM_Standalone)
	{
		//Show offline UI


	}

	if (GetNetMode() == ENetMode::NM_Client)
	{
		//Show connected client UI
		
		//Send Player Information
		UVehicleUE5GameInstance* gInstance = Cast<UVehicleUE5GameInstance>(GetWorld()->GetGameInstance());
		if (gInstance)
		{
			SetPlayerInfo(gInstance->PlayerName);
		}

	}

}

void AVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AVehiclePlayerController::RotateCarCamera(const FVector2D pos)
{
	
}

void AVehiclePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	check(PlayerState)

	OnNewPlayerStateReceived.Broadcast(Cast<AVehiclePlayerState>(PlayerState));
}

void AVehiclePlayerController::SetPlayerInfo_Implementation(const FString& CandidateName)
{
	//Set Player Properties
	AVehicleUE5GameMode* gm = Cast<AVehicleUE5GameMode>(GetWorld()->GetAuthGameMode());

	if (gm)
	{
		AVehiclePlayerState* pState = Cast<AVehiclePlayerState>(PlayerState);
		pState->SetPlayerNickName(CandidateName);
	}
}

bool AVehiclePlayerController::SetPlayerInfo_Validate(const FString& CandidateName)
{
	return GetLocalRole() == ROLE_Authority;
}

void AVehiclePlayerController::ServerPlayerChatMessage_Implementation(const FString& chatMessage)
{
	// Send Player Chat Messages
}

bool AVehiclePlayerController::ServerPlayerChatMessage_Validate(const FString& chatMessage)
{
	return GetLocalRole() == ROLE_Authority;
}

float AVehiclePlayerController::GetServerTime()
{
	float newtime = 0.f;
	if (GetWorld() && GetWorld()->GetGameState())
	{
	//	newtime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();	
	}
	return newtime;
}

void AVehiclePlayerController::SelectCarColor_Implementation(int32 ColorIndex)
{
	if (GetWorld()->GetAuthGameMode())
	{
		AVehicleUE5Pawn* pawn = Cast<AVehicleUE5Pawn>(this->GetPawn());
		if (pawn->IsValidLowLevel())
		{

			AVehiclePlayerState* pState = Cast<AVehiclePlayerState>(PlayerState);
			if (pState)
			{
				//pState->SetColorId(ColorIndex);
				UE_LOG(LogTemp, Warning, TEXT("Called Material Change on Server"));
			}

		}
	}
}

bool AVehiclePlayerController::SelectCarColor_Validate(int32 ColorIndex)
{
	return GetLocalRole() == ROLE_Authority;
}

void AVehiclePlayerController::StartPlayerGame_Implementation()
{
	//Start the game on Server
}

bool AVehiclePlayerController::StartPlayerGame_Validate()
{
	return GetLocalRole() == ENetRole::ROLE_Authority;
}

void AVehiclePlayerController::StartOfflineGame()
{
	GetPawn()->EnableInput(this);
	AVehicleUE5Pawn* VehiclePawn =  Cast<AVehicleUE5Pawn>(GetPawn());

	check(VehiclePawn)

	VehiclePawn->StopWelcomeScreenCameraRotation();
}