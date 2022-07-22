// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VehiclePlayerState.h"
#include "Online.h"
#include "VehiclePlayerController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, AVehiclePlayerState*, NewPlayerState);

UCLASS()
class VEHICLEUE5_API AVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()


	AVehiclePlayerController();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	virtual void OnRep_PlayerState() override;

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateChanged OnNewPlayerStateReceived;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void SetPlayerInfo(const FString& CandidateName);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerPlayerChatMessage(const FString& chatMessage);

	UFUNCTION(BlueprintCallable)
	float GetServerTime();

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable)
	void StartPlayerGame();

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable)
	void SelectCarColor(int32 ColorIndex);

	UFUNCTION(BlueprintCallable)
	void StartOfflineGame();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCameraMove;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString sessionStringID;

	UFUNCTION(BlueprintCallable)
	void RotateCarCamera(const FVector2D pos);

	UFUNCTION(BlueprintCallable)
	void TravelToServer(FString sURL);

	UFUNCTION(BlueprintCallable,Server,Reliable,WithValidation)
	void ResetPosition();

	virtual void OnUnPossess() override;

	virtual void OnPossess(APawn* aPawn) override;

	UFUNCTION(BlueprintCallable)
	AVehiclePlayerState* GetVehiclePlayerState() { return VehiclePlayerState; }

	

private:
	UPROPERTY()
	AVehiclePlayerState* VehiclePlayerState;
};
