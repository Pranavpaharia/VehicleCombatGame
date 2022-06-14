// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VehicleUE5Hud.generated.h"

UCLASS(config = Game)
class AVehicleUE5Hud : public AHUD
{
	GENERATED_BODY()

public:
	AVehicleUE5Hud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
