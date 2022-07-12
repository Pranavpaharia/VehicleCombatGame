// Fill out your copyright notice in the Description page of Project Settings.
#include "Abilities/VehicleAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UVehicleAbilitySystemComponent::UVehicleAbilitySystemComponent()
{

}

int32 UVehicleAbilitySystemComponent::GetDefaultAbilityLevel() const
{
	return 1;
}

UVehicleAbilitySystemComponent* UVehicleAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent /* = false */)
{
	return Cast<UVehicleAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor,LookForComponent));
}

void UVehicleAbilitySystemComponent::ReceiveDamage(UVehicleAbilitySystemComponent* SourceARC, float UnmitigatedDamage, float MitigatedDamage)
{
	OnReceiveDamage.Broadcast(SourceARC, UnmitigatedDamage, MitigatedDamage);
}