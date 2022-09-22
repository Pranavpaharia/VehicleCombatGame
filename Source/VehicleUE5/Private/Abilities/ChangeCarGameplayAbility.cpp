// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ChangeCarGameplayAbility.h"
#include "VehicleUE5Pawn.h"

UChangeCarGameplayAbility::UChangeCarGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTag AbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.ChangeCar"));
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
}

void UChangeCarGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Warning, TEXT("Try Activating ChangeCar Ability"));

	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetAvatarActorFromActorInfo());

	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && VehiclePawn)
	{
		VehiclePawn->IncreamentSkeletalMeshIndex();
		UE_LOG(LogTemp, Warning, TEXT("On Server Running ChangeCar Ability"));
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}