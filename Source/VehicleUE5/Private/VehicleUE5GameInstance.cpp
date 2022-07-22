// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleUE5GameInstance.h"
#include "VehicleUE5GameMode.h"
#include "OnlineSubsystemUtils.h"

UVehicleUE5GameInstance::UVehicleUE5GameInstance()
{

}

void UVehicleUE5GameInstance::Init()
{
	Super::Init();
}

void UVehicleUE5GameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

void UVehicleUE5GameInstance::SetPlayerName(FString const& name)
{
	PlayerName = name;
}

TSharedPtr< const FUniqueNetId > UVehicleUE5GameInstance::GetUniqueNetIdFromControllerId(const int ControllerId)
{
	IOnlineIdentityPtr OnlineIdentityInt = Online::GetIdentityInterface(GetWorld());

	if (OnlineIdentityInt.IsValid())
	{
		TSharedPtr<const FUniqueNetId> UniqueId = OnlineIdentityInt->GetUniquePlayerId(ControllerId);
	
		if (UniqueId.IsValid())
		{
			return UniqueId;
		}
	}

	return nullptr;
}

AVehicleGameSession* UVehicleUE5GameInstance::GetGameSession() const
{
	UWorld* const world = GetWorld();
	if (world)
	{
		AVehicleUE5GameMode* const gamemode = Cast<AVehicleUE5GameMode>(world->GetAuthGameMode());
		if (gamemode)
		{
			return Cast<AVehicleGameSession>(gamemode->GameSession);
		}
	}

	return nullptr;
}

//void UVehicleUE5GameInstance::FindSessionsOnline_Implementation(ULocalPlayer* PlayerOwner, bool bIsDedicatedServer)
//{
//	bool bResult = false;
//
//	check(PlayerOwner)
//	if (PlayerOwner)
//	{
//		AVehicleGameSession* const GameSession = GetGameSession();
//		if (GameSession)
//		{
//			GameSession->FindSessions(PlayerOwner->GetPreferredUniqueNetId().GetUniqueNetId(), NAME_GameSession, false, false);
//			UE_LOG(LogTemp, Warning, TEXT("Find Session Called"));
//			
//		}
//
//
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Find Session Failed"));
//	}
//	
//
//}
//
//bool UVehicleUE5GameInstance::FindSessionsOnline_Validate(ULocalPlayer* PlayerOwner, bool bIsDedicatedServer)
//{
//	return true;
//}


void UVehicleUE5GameInstance::FindSessionsOnline(ULocalPlayer* PlayerOwner, bool bIsDedicatedServer)
{
	bool bResult = false;

	check(PlayerOwner)
		if (PlayerOwner)
		{
			AVehicleGameSession* const GameSession = GetGameSession();
			if (GameSession)
			{
				GameSession->FindSessions(PlayerOwner->GetPreferredUniqueNetId().GetUniqueNetId(), NAME_GameSession, false, false);
				UE_LOG(LogTemp, Warning, TEXT("Find Session Called"));

			}


		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Session Failed"));
		}


}


void UVehicleUE5GameInstance::GetCurrentSessionID_AsString(UObject* WordlContextObject, FString& SessionID)
{
	UWorld* const World = GEngine->GetWorldFromContextObject(WordlContextObject, EGetWorldErrorMode::LogAndReturnNull);
	IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);

	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCurrentSessionID_AsString couldn't get the session interface!"));
		SessionID.Empty();
		return;
	}

	const FNamedOnlineSession* NamedSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (NamedSession != nullptr)
	{
		const TSharedPtr<FOnlineSessionInfo> SessionInfo = NamedSession->SessionInfo;
		if (SessionInfo.IsValid() && SessionInfo->IsValid() && SessionInfo->GetSessionId().IsValid())
		{
			SessionID = SessionInfo->GetSessionId().ToString();
			return;
		}

		SessionID.Empty();
	}
}