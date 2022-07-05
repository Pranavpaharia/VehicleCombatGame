// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleGameState.h"

AVehicleGameState::AVehicleGameState()
{
	VehiclePlayerStateList.Empty();
}

void AVehicleGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void AVehicleGameState::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

void AVehicleGameState::AddPlayerState(APlayerState* PlayerState)
{
	AVehiclePlayerState* vehplayerState = Cast<AVehiclePlayerState>(PlayerState);
	check(vehplayerState)
	VehiclePlayerStateList.Add(vehplayerState);
	UE_LOG(LogTemp, Warning, TEXT("Player State of: %s is added"), *vehplayerState->GetCandidateName());
}

void AVehicleGameState::RemovePlayerState(APlayerState* PlayerState)
{
	AVehiclePlayerState* vehplayerState = Cast<AVehiclePlayerState>(PlayerState);
	check(vehplayerState)
	
	if (VehiclePlayerStateList.Contains(vehplayerState))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player State of: %s is removed"), *vehplayerState->GetCandidateName());
		VehiclePlayerStateList.Remove(vehplayerState);
	}
}