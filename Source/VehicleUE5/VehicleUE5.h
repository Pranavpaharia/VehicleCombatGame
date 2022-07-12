// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class VehicleBasicAbilityID : uint8
{
	Alive,
	Dead
};

UENUM(BlueprintType)
enum class VehiclePowerAbilityID : uint8
{
	FireBullets,
	FireRockets,
	Mines,
	Shield
};


UENUM(BlueprintType)
enum class ETypesOfVehicleID : uint8
{
	Vehicle01,
	Vehicle02,
	Vehicle03
};
