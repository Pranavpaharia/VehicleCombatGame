// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VehiclePlayerState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCandidateNameChanged, FString, candidateName);
DECLARE_DELEGATE_OneParam(FOnSetColorIdEvent,const int32);


UCLASS()
class VEHICLEUE5_API AVehiclePlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	AVehiclePlayerState();

	virtual void ClientInitialize(class AController* InController) override;

	virtual void RegisterPlayerWithSession(bool bWasFromInvite) override;

	virtual void UnregisterPlayerWithSession() override;

	virtual void CopyProperties(APlayerState* PlayerState) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_ColorId)
	int32 ColorId;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing = OnRep_CandidateName)
	FString CandidateName;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing = OnRep_TextChat)
	FString TextChat;

	UFUNCTION()
	void OnRep_ColorId();

	UFUNCTION()
	void OnRep_CandidateName();

	UFUNCTION()
	void OnRep_TextChat();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnReplicatedTextChat(FString const& PlayerName, FString const& Message);

	virtual void PostInitializeComponents() override;

	FORCEINLINE const FString GetCandidateName() const {
		return CandidateName;
	}

	UFUNCTION(BlueprintCallable)
	void SetPlayerNickName(FString Name);

	UFUNCTION(BlueprintCallable)
	void UpdateChatMessage(FString Name);

	UPROPERTY(BlueprintAssignable)
	FOnCandidateNameChanged OnCandidateNameChanged;


	//UPROPERTY(BlueprintAssignable)
	FOnSetColorIdEvent OnSetColorEvent;

	UFUNCTION()
	void SetColorId(uint8 colorIndex);

	
};
