// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Abilities/VehicleAbilitySystemComponent.h"
#include "Abilities/VehicleAttributeSet.h"
#include "VehiclePlayerState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCandidateNameChanged, FString, candidateName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetColorIdEvent, int32, colorID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetSessionString, FString , sessionstringID);


UCLASS()
class VEHICLEUE5_API AVehiclePlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	AVehiclePlayerState();

	virtual void BeginPlay() override;

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

	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing = OnRep_sessionStringID)
	FString sessionStringID;

	UFUNCTION()
	void OnRep_ColorId();

	UFUNCTION()
	void OnRep_CandidateName();

	UFUNCTION()
	void OnRep_TextChat();

	UFUNCTION()
	void OnRep_sessionStringID();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnReplicatedTextChat(FString const& PlayerName, FString const& Message);

	virtual void PostInitializeComponents() override;


public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerNickName(FString Name);

	UFUNCTION(BlueprintCallable)
	void UpdateChatMessage(FString Name);

	UPROPERTY(BlueprintAssignable)
	FOnCandidateNameChanged OnCandidateNameChanged;

	UPROPERTY(BlueprintAssignable)
	FOnSetColorIdEvent OnSetColorEvent;

	UPROPERTY(BlueprintAssignable)
	FOnSetSessionString OnSetSessionStringEvent;


	UFUNCTION()
	void SetColorId(uint8 colorIndex);

	UFUNCTION()
	void SetSessionIDString(FString str);

	FORCEINLINE const FString GetCandidateName() const {
		return CandidateName;
	}

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UVehicleAttributeSet* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetMaxMana() const;


protected:
	UPROPERTY()
	class UVehicleAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UVehicleAttributeSet* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnVehicleDamageHit(const FGameplayTag CallbackTag, int32 NewCount);


	
};
