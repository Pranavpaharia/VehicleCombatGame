// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/VehicleGameplayAbility.h"
#include "Abilities/VehicleAbilitySystemComponent.h"

UVehicleGameplayAbility::UVehicleGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
	

	ActivationBlockedTags.AddTag((FGameplayTag::RequestGameplayTag(FName("State.Dead"))));
	//ActivationBlockedTags.AddTag((FGameplayTag::RequestGameplayTag(FName(""))));
}

void UVehicleGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		/*if (ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, true))
		{
			UE_LOG(LogTemp, Warning, TEXT("Ability Activated  "));
		}*/
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, true);
		
		if (ActivatedAbility)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ability Activated  "));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ability Can't be Activated  "));
		}

	}
}

bool UVehicleGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return false;
	}
	

	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UVehicleGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
}

void UVehicleGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
