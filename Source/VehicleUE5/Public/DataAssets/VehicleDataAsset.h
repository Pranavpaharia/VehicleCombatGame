// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimBlueprint.h"
#include "VehicleUE5/VehicleUE5.h"
#include "VehicleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UVehicleDataAsset : public UDataAsset
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	USkeletalMesh* CarSkeletalMesh;

	UPROPERTY(EditAnywhere)
	UAnimBlueprint* CarAnimationBlueprint;

	UPROPERTY(EditAnywhere)
	ETypesOfVehicleID CarTypeId;
};
