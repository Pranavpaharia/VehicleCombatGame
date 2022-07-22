// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VehicleBeaconHostObject.h"
#include "VehicleBeaconClient.h"
#include "VehicleUE5Pawn.h"
#include "VehiclePlayerController.h"
#include "VehicleUE5GameMode.generated.h"

UCLASS(MinimalAPI)
class AVehicleUE5GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AVehicleUE5GameMode();

	UFUNCTION()
	bool SpawnHostBeacon();

	UFUNCTION()
	bool SpawnClientBeacon();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AVehicleBeaconHostObject* ServerBeacon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AVehicleBeaconClient* ClientBeacon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString sessionStringID;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ConnectToDedicatedServer(const FString& address);

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;


	//Blueprint Access Parameters
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AVehicleUE5Pawn> CarPawnClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AVehiclePlayerController> ControllerClass;

	virtual void SetMatchState(FName NewState) override;

	virtual void OnMatchStateSet() override;

	virtual void NotifyPendingConnectionLost(const FUniqueNetIdRepl& ConnectionUniqueId) override;

	virtual void HandleDisconnect(UWorld* InWorld, UNetDriver* NetDriver) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void SendSessionIDToClient(APlayerController* NewPlayer);


};



