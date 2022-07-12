// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/VehicleAttributeSet.h"

UVehicleAttributeSet::UVehicleAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, NitroMana(1.f)
	, NitroMaxMana(1.f)
{

}

void UVehicleAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UVehicleAttributeSet, Health);
	DOREPLIFETIME(UVehicleAttributeSet, MaxHealth);
	DOREPLIFETIME(UVehicleAttributeSet, NitroMana);
	DOREPLIFETIME(UVehicleAttributeSet, NitroMaxMana);

}

void UVehicleAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVehicleAttributeSet, Health, OldValue);
}

void UVehicleAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVehicleAttributeSet, MaxHealth, OldValue);
}

void UVehicleAttributeSet::OnRep_NitroMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVehicleAttributeSet, NitroMana, OldValue);
}

void UVehicleAttributeSet::OnRep_NitroMaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVehicleAttributeSet, NitroMaxMana, OldValue);
}

void UVehicleAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UVehicleAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}