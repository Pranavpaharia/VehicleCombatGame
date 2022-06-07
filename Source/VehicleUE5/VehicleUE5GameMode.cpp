// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleUE5GameMode.h"
#include "VehicleUE5Pawn.h"
#include "VehicleUE5Hud.h"

AVehicleUE5GameMode::AVehicleUE5GameMode()
{
	DefaultPawnClass = AVehicleUE5Pawn::StaticClass();
	//HUDClass = AVehicleUE5Hud::StaticClass();
}
