// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "GameFramework/GameSession.h"
#include "VehicleGameSession.generated.h"


UENUM(BlueprintType)
enum SessionType
{
	None,
	Created,
	Started,
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnStartSessionComplete, bool, Successful);

UCLASS()
class VEHICLEUE5_API AVehicleGameSession : public AGameSession
{
	GENERATED_BODY()

	AVehicleGameSession();

	//virtual FString ApproveLogin(const FString& Options);
	
	virtual void OnAutoLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& Error) override;

	virtual void RegisterServer() override;

	virtual void RegisterServerFailed() override;

	virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite) override;

	bool bGameSessionCreated;

	SessionType CurrentSessionType = SessionType::None;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FCSOnStartSessionComplete OnStartSessionCompleteEvent;


	virtual void OnCreateSessionComplete(FName SsName, bool bWasSuccessful);

	void StartSession();

	void OnStartOnlineGameComplete(FName SsName, bool bWasSuccessful);
};
