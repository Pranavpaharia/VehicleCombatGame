// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EVehicleBasicAbilityID : uint8
{
	Alive,
	Dead
};

UENUM(BlueprintType)
enum class EVehiclePowerAbilityID : uint8
{
	FireBullets,
	FireRockets,
	Mines,
	Shield,
	NitroBoost,
	Confirm,
	Cancel,
	None
};


UENUM(BlueprintType)
enum class ETypesOfVehicleID : uint8
{
	Vehicle01,
	Vehicle02,
	Vehicle03
};

UENUM(BlueprintType)
enum class EPlayerConnectionType : uint8
{
	LocalConnection,
	OnlineConnection
};
