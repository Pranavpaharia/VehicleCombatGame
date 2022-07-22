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
DECLARE_MULTICAST_DELEGATE_TwoParams(FCSOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful);


UCLASS()
class VEHICLEUE5_API AVehicleGameSession : public AGameSession
{
	GENERATED_BODY()

public:

	AVehicleGameSession();

	//virtual FString ApproveLogin(const FString& Options);
	
	virtual void OnAutoLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& Error) override;

	virtual void RegisterServer() override;

	virtual void RegisterServerFailed() override;

	virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite) override;

	virtual void UnregisterPlayer(const APlayerController* ExitingPlayer) override;

	virtual void UnregisterPlayers(FName InSessionName, const TArray<FUniqueNetIdRepl>& Players) override;

	bool bGameSessionCreated;

	SessionType CurrentSessionType = SessionType::None;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FCSOnStartSessionComplete OnStartSessionCompleteEvent;

	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	FCSOnFindSessionsComplete OnFindSessionCompleteEvent;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;


	

	virtual void OnCreateSessionComplete(FName SsName, bool bWasSuccessful);

	void StartSession();

	
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName InSessionName, bool bIsLan, bool bIsPresence);

	void OnStartOnlineGameComplete(FName SsName, bool bWasSuccessful);

	void UpdateSessionJoinability(FName InSessionName, bool bPublicSearchable, bool bAllowInvites, bool bJoinViaPresence, bool bJoinViaPresenceFriendsOnly) override;

	void OnFindSessionCompleted(bool bSuccessful);

};
