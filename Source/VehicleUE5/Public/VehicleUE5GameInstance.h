// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemUtils.h"
#include "VehicleGameSession.h"
#include "VehicleUE5GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UVehicleUE5GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UVehicleUE5GameInstance();

	virtual void Init() override;

	virtual void StartGameInstance() override;


	TSharedPtr< const FUniqueNetId > GetUniqueNetIdFromControllerId(const int ControllerId);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FString PlayerName;

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString const& name);

	AVehicleGameSession* GetGameSession() const;

	UFUNCTION(BlueprintCallable)
	void FindSessionsOnline(ULocalPlayer* PlayerOwner, bool bIsDedicatedServer);

	void GetCurrentSessionID_AsString(UObject* WordlContextObject, FString& SessionID);
};
