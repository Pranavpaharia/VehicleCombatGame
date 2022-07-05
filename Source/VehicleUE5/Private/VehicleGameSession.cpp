// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleGameSession.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Engine/World.h"


AVehicleGameSession::AVehicleGameSession()
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &AVehicleGameSession::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &AVehicleGameSession::OnStartOnlineGameComplete);
	SessionName = FName("VehicleServerSession");
}

//FString AVehicleGameSession::ApproveLogin(const FString& Options)
//{
//	Super::ApproveLogin(Options);
//
//	return Options;
//}

void AVehicleGameSession::OnAutoLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& Error)
{
	Super::OnAutoLoginComplete(LocalUserNum, bWasSuccessful, Error);
}

void AVehicleGameSession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite)
{
	Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);
}

void AVehicleGameSession::RegisterServer()
{
	Super::RegisterServer();
	UE_LOG(LogTemp, Warning, TEXT("Register Server Called"));

	//Create Session on Server
	if (!bGameSessionCreated)
	{
		IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());

		if (OnlineSub)
		{
			IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
			if (SessionInterface.IsValid())
			{

				if (SessionInterface->GetNumSessions() > 0)
					return;

				FOnlineSessionSettings* sessionSettings = new FOnlineSessionSettings();
				sessionSettings->bIsLANMatch = true;
				sessionSettings->bShouldAdvertise = true;
				sessionSettings->bIsDedicated = true;
				sessionSettings->bAllowInvites = true;
				sessionSettings->bUseLobbiesIfAvailable = true;
				sessionSettings->bUseLobbiesVoiceChatIfAvailable = true;
				sessionSettings->bAllowJoinInProgress = true;
				sessionSettings->bAllowJoinViaPresence = true;
				sessionSettings->bUsesPresence = true;
				sessionSettings->NumPrivateConnections = 10;
				sessionSettings->NumPublicConnections = 10;
				sessionSettings->Set(SETTING_MAPNAME, FString("ServerMap"), EOnlineDataAdvertisementType::ViaOnlineService);

				OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

				if (SessionInterface->CreateSession(0, NAME_GameSession, *sessionSettings))
				{
					UE_LOG(LogTemp, Warning, TEXT("Creating Session Successfully triggered!"));
				}
			}
		}

	}
}

void AVehicleGameSession::OnCreateSessionComplete(FName SsName, bool bWasSuccessful)
{
	const IOnlineSessionPtr sessionInterface = Online::GetSessionInterface(GetWorld());
	if (sessionInterface)
	{
		sessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
	}

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Called OnCreateSessionComplete"));
		bGameSessionCreated = true;
		CurrentSessionType = SessionType::Created;
		StartSession();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed  OnCreateSessionComplete"));
	}
}

void AVehicleGameSession::StartSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting Session...."));

	const IOnlineSessionPtr sessionInterface = Online::GetSessionInterface(GetWorld());
	
	OnStartSessionCompleteDelegateHandle =
		sessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

	if (sessionInterface->StartSession(NAME_GameSession))
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Session Method Called"));
	}
	else
	{
		sessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		UE_LOG(LogTemp, Warning, TEXT("Starting Session Method FAILED!"));
		//OnStartSessionCompleteEvent.Broadcast(false);
	}
}

void AVehicleGameSession::OnStartOnlineGameComplete(FName SsName, bool bWasSuccessful)
{
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnStartOnlineGameComplete Called"));
		
		// tell non-local players to start online game
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			/*ALudoPlayerController* PC = Cast<ALudoPlayerController>(*It);
			if (PC && !PC->IsLocalPlayerController())
			{
				PC->ClientStartOnlineGame();
			}*/
		}

		//GetWorld()->ServerTravel(TEXT("/Game/Maps/ServerGameMap?listen"), true, true);
	}
}

void AVehicleGameSession::RegisterServerFailed()
{
	Super::RegisterServerFailed();
}