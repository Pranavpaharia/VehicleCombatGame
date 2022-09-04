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
	ChangeVehicle,
	HandBrake,
	Confirm,
	Cancel,
	None
};

UENUM(BlueprintType)
enum class EVehicleAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
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


UENUM(BlueprintType)
enum class EVechicleAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};
