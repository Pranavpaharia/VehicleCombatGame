// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "VehiclePlayerState.h"
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

	virtual void AddPlayerState(APlayerState* PlayerState) override;

	virtual void RemovePlayerState(APlayerState* PlayerState) override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnNewPlayerChatMessage OnNewPlayerChatMessage;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<AVehiclePlayerState*> VehiclePlayerStateList;


	
};
