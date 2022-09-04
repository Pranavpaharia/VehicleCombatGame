// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/VehicleHandBrakeGameplayAbility.h"
#include "VehicleUE5Pawn.h"

UVehicleHandBrakeGameplayAbility::UVehicleHandBrakeGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTag AbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.HandBrake"));
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
}

void UVehicleHandBrakeGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Warning, TEXT("Try Activating Shield  Ability"));

	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetAvatarActorFromActorInfo());

	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && VehiclePawn)
	{
		VehiclePawn->OnHandbrakePressed();

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}