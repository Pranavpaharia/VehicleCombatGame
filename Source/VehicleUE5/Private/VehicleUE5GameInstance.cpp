// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleUE5GameInstance.h"

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