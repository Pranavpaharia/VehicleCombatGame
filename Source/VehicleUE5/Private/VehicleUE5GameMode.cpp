// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleUE5GameMode.h"
#include "VehicleUE5Pawn.h"
#include "VehicleUE5Hud.h"
#include "VehiclePlayerController.h"
#include "VehiclePlayerState.h"
#include "VehicleGameState.h"
#include "VehicleGameSession.h"
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

	
}
