// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/VehicleGameplayAbility.h"

UVehicleGameplayAbility::UVehicleGameplayAbility()
{

}

void UVehicleGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
}
