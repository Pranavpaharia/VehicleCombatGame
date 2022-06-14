// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "VehicleGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewPlayerChatMessage, FString, chatMsg);

UCLASS()
class VEHICLEUE5_API AVehicleGameState : public AGameState
{
	GENERATED_BODY()

	AVehicleGameState();

	virtual void HandleMatchHasStarted() override;

	virtual void HandleMatchHasEnded() override;

	UPROPERTY(BlueprintAssignable)
	FOnNewPlayerChatMessage OnNewPlayerChatMessage;


	
};
