// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePlayerState.h"
#include "Net/OnlineEngineInterface.h"
#include "Net/UnrealNetwork.h"
#include "VehiclePlayerController.h"

AVehiclePlayerState::AVehiclePlayerState()
{
	ColorId = 1;
	CandidateName = TEXT("");
	TextChat = TEXT("-.^");
}

void AVehiclePlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AVehiclePlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AVehiclePlayerState* LudoPlayer = Cast<AVehiclePlayerState>(PlayerState);

	if (LudoPlayer)
	{
		LudoPlayer->ColorId = ColorId;
	}
}

void AVehiclePlayerState::ClientInitialize(class AController* InController)
{
	Super::ClientInitialize(InController);
	AVehiclePlayerController* pc = Cast<AVehiclePlayerController>(InController);
	if (pc)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller broadcast player state"));
		pc->OnNewPlayerStateReceived.Broadcast(this);
	}

}

void AVehiclePlayerState::RegisterPlayerWithSession(bool bWasFromInvite)
{
	if (UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(),NAME_GameSession))
	{
		Super::RegisterPlayerWithSession(bWasFromInvite);
	}
}

void AVehiclePlayerState::UnregisterPlayerWithSession()
{
	if (!IsFromPreviousLevel() && UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(), FName("LudoSessionName")))
	{
		Super::UnregisterPlayerWithSession();
	}
}

void AVehiclePlayerState::SetColorId(uint8 colorIndex)
{
	ColorId = colorIndex;
}

void AVehiclePlayerState::OnRep_ColorId()
{
	UE_LOG(LogTemp, Warning, TEXT("On Rep_ColorId is: %d"), ColorId);
	OnSetColorEvent.Broadcast(ColorId);
}

void AVehiclePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVehiclePlayerState, ColorId);
	DOREPLIFETIME(AVehiclePlayerState, CandidateName);
	DOREPLIFETIME(AVehiclePlayerState, TextChat);

}

void AVehiclePlayerState::OnRep_TextChat()
{
	UE_LOG(LogTemp, Warning, TEXT("Chat Message Replicated:  %s"), *TextChat);
	//OnCandidateNameChanged.Broadcast(TextChat);
	OnReplicatedTextChat(CandidateName, TextChat);
}

void AVehiclePlayerState::OnRep_CandidateName()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Name Replicated. Its called %s"), *CandidateName);
	OnCandidateNameChanged.Broadcast(CandidateName);
}

void AVehiclePlayerState::SetPlayerNickName(FString Name)
{
	CandidateName = Name;
}

void AVehiclePlayerState::UpdateChatMessage(FString Msg)
{
	TextChat = Msg;
}
