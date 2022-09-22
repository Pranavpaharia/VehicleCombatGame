// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ShieldVehicleGameplayAbility.h"

#include "VehicleUE5Pawn.h"

UShieldVehicleGameplayAbility::UShieldVehicleGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTag AbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Immunity"));
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
}

void UShieldVehicleGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
		UE_LOG(LogTemp, Warning, TEXT("Calling On Server"));

		const FGameplayEffectSpecHandle ImmunityEffectSpecHandle = MakeOutgoingGameplayEffectSpec(ShieldGameplayEffect, GetAbilityLevel());
		
		/*FGameplayEffectContextHandle contextHandle = ImmunityEffectSpecHandle.Data->GetEffectContext();
		contextHandle.AddInstigator(VehiclePawn, VehiclePawn);
		ImmunityEffectSpecHandle.Data.Get()->Initialize(Cast<UGameplayEffect>(ShieldGameplayEffect), contextHandle, GetAbilityLevel());
		FGameplayEffectSpec* Spec = ImmunityEffectSpecHandle.Data.Get();*/

		/*if (!Spec)
		{
			VehiclePawn->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*Spec);
			UE_LOG(LogTemp, Warning, TEXT("Applied Immunity Effect on Server"));
		}*/

		FGameplayEffectContextHandle EffectContext = VehiclePawn->GetAbilitySystemComponent()->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = VehiclePawn->GetAbilitySystemComponent()->MakeOutgoingSpec(ShieldGameplayEffect, GetAbilityLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = VehiclePawn->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), VehiclePawn->GetAbilitySystemComponent());
			UE_LOG(LogTemp, Warning, TEXT("Gameplay Effect is Applied to Self on Server"));
		}


		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

}