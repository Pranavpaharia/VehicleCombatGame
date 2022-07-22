// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePlayerState.h"
#include "Net/OnlineEngineInterface.h"
#include "Net/UnrealNetwork.h"
#include "VehicleUE5Pawn.h"
#include "Widgets/VehicleBaseInfoWidget.h"
#include "VehiclePlayerController.h"

AVehiclePlayerState::AVehiclePlayerState()
{
	ColorId = 1;
	CandidateName = TEXT("");
	TextChat = TEXT("-.^");
	sessionStringID = TEXT("");

	AbilitySystemComponent = CreateDefaultSubobject<UVehicleAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UVehicleAttributeSet>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100;
	
	DeadTag = FGameplayTag::RequestGameplayTag((FName("State.Dead")));
}

void AVehiclePlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AVehiclePlayerState::OnHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetNitroManaAttribute()).AddUObject(this, &AVehiclePlayerState::OnManaChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AVehiclePlayerState::OnMaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetNitroManaAttribute()).AddUObject(this, &AVehiclePlayerState::OnMaxManaChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.DamageHit")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AVehiclePlayerState::OnVehicleDamageHit);
	}
	
	
}

UAbilitySystemComponent* AVehiclePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UVehicleAttributeSet* AVehiclePlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool AVehiclePlayerState::IsAlive() const
{
	return true;
}

void AVehiclePlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	AVehiclePlayerController* PC = Cast<AVehiclePlayerController>(GetOwner());
	if (PC)
	{

	}
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
		UE_LOG(LogTemp, Warning, TEXT("AVehiclePlayerState::ClientInitialize"));
		pc->OnNewPlayerStateReceived.Broadcast(this);
	}

}

void AVehiclePlayerState::RegisterPlayerWithSession(bool bWasFromInvite)
{
	if (UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(),NAME_GameSession))
	{
		Super::RegisterPlayerWithSession(bWasFromInvite);
		UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("GameSession"));


		UE_LOG(LogTemp, Warning, TEXT("Register Player with Session %s"), *(EnumPtr ? EnumPtr->GetNameStringByIndex(static_cast<uint8>(NAME_GameSession)) : TEXT("Invalid Enum")));
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
	DOREPLIFETIME(AVehiclePlayerState, sessionStringID);

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

void AVehiclePlayerState::OnRep_sessionStringID()
{
	UE_LOG(LogTemp, Warning, TEXT("Session ID replicated:  %s"), *sessionStringID);
	OnSetSessionStringEvent.Broadcast(sessionStringID);
}

void AVehiclePlayerState::SetPlayerNickName(FString Name)
{
	CandidateName = Name;
}

void AVehiclePlayerState::UpdateChatMessage(FString Msg)
{
	TextChat = Msg;
}

void AVehiclePlayerState::SetSessionIDString(FString str)
{
	sessionStringID = str;
}

float AVehiclePlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float AVehiclePlayerState::GetMaxHealth() const
{
	return  AttributeSetBase->GetMaxHealth();
}

float AVehiclePlayerState::GetMana() const
{
	return AttributeSetBase->GetNitroMana();
}

float AVehiclePlayerState::GetMaxMana() const
{
	return AttributeSetBase->GetNitroMaxMana();
}

void AVehiclePlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	//Set Health on vehicle Pawn and UI Widgets
	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetPawn());
	if (VehiclePawn && GetLocalRole() != ROLE_Authority)
	{
		UVehicleBaseInfoWidget* PlayerInfoWidget = VehiclePawn->GetFloatingStatusBar();
		if (PlayerInfoWidget)
		{
			PlayerInfoWidget->SetHealthBar(Health / GetMaxHealth());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("On Player State: On Health Changed to %f"), Health);

	//If the player dies, handle health

	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		//Get the Pawn and set dying animation 
		VehiclePawn->VehicleDie();
	}
}

void AVehiclePlayerState::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;
	UE_LOG(LogTemp, Warning, TEXT("On Player State: OnMaxHealthChanged to %f"), MaxHealth);
	//Update Pawn Character HUD 

	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetPawn());
	check(VehiclePawn)
	if (VehiclePawn && GetLocalRole() != ROLE_Authority)
	{
		UVehicleBaseInfoWidget* PlayerInfoWidget = VehiclePawn->GetFloatingStatusBar();
		check(PlayerInfoWidget)
		if (PlayerInfoWidget)
		{
			PlayerInfoWidget->SetHealthBar(GetHealth() / MaxHealth);
		}
	}

}

void AVehiclePlayerState::OnManaChanged(const FOnAttributeChangeData& Data)
{
	float Mana = Data.NewValue;

	UE_LOG(LogTemp, Warning, TEXT("On Player State: OnManaChanged to %f"), Mana);
	
	//Update Mana on vehicle pawn and UI widgets
	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetPawn());
	if (VehiclePawn && GetLocalRole() != ROLE_Authority)
	{
		UVehicleBaseInfoWidget* HeroFloatingStatusBar = VehiclePawn->GetFloatingStatusBar();
		if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetNitroManaBar(Mana / GetMaxMana());
		}
	}


}

void AVehiclePlayerState::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
	float MaxMana = Data.NewValue;

	UE_LOG(LogTemp, Warning, TEXT("On Player State: OnMaxManaChanged to %f"), MaxMana);

	//Update Pawn Character HUD 

	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetPawn());
	if (VehiclePawn && GetLocalRole() != ROLE_Authority)
	{
		UVehicleBaseInfoWidget* HeroFloatingStatusBar = VehiclePawn->GetFloatingStatusBar();
		if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetNitroManaBar(GetMana() / MaxMana);
		}
	}
}

void AVehiclePlayerState::OnVehicleDamageHit(const FGameplayTag CallbackTag, int32 NewCount)
{

}

