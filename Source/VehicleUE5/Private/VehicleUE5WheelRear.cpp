// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleUE5WheelRear.h"
#include "UObject/ConstructorHelpers.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

UVehicleUE5WheelRear::UVehicleUE5WheelRear()
{
	WheelRadius = 18.f;
	WheelWidth = 20.0f;
	FrictionForceMultiplier = 2.0f;
	CorneringStiffness = 500.0f;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = false;
	AxleType = EAxleType::Rear;
	SpringRate = 200.0f;
	SpringPreload = 100.f;
	SuspensionDampingRatio = 0.5f;
	WheelLoadRatio = 0.0f;
	RollbarScaling = 0.5f;
	SuspensionMaxRaise = 8;
	SuspensionMaxDrop = 12.0f;
	WheelLoadRatio = 0.5f;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS
