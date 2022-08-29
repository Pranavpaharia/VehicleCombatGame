// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/FireLaserGameplayAbility.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "VehicleUE5Pawn.h"

UFireLaserGameplayAbility::UFireLaserGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTag AbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.LaserGun"));
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));

	Range = 1000.0f;
	Damage = 10.0f;
}

void UFireLaserGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Warning, TEXT("Try Activating Ability"));

	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetAvatarActorFromActorInfo());

	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && VehiclePawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Bullet"));

		FVector Start = VehiclePawn->GetActorLocation();
		FVector End = VehiclePawn->GetInternalCameraSceneComponent()->GetComponentLocation() + VehiclePawn->GetInternalCameraSceneComponent()->GetForwardVector() * Range;
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());

		DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

		FTransform MuzzleTransform = VehiclePawn->GetTransform();
		MuzzleTransform.SetLocation(VehiclePawn->GetActorLocation() + FVector::UpVector * 30 + VehiclePawn->GetActorForwardVector() * 200);
		MuzzleTransform.SetRotation(FRotator(0, Rotation.Yaw, 0).Quaternion());
	//	MuzzleTransform.SetScale3D(FVector(1.0f));

		FActorSpawnParameters SpawnParamters;
		SpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ALaserProjectile* Projectile = GetWorld()->SpawnActorDeferred<ALaserProjectile>(LaserProjectileClass, MuzzleTransform, GetOwningActorFromActorInfo(), VehiclePawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
		Projectile->Range = Range;
		Projectile->FinishSpawning(MuzzleTransform);

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	else if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_SimulatedProxy && VehiclePawn)
	{
		VehiclePawn->PlayFireSound();
	}
}

void UFireLaserGameplayAbility::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UFireLaserGameplayAbility::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UFireLaserGameplayAbility::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	AVehicleUE5Pawn* VehiclePawn = Cast<AVehicleUE5Pawn>(GetAvatarActorFromActorInfo());

	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && VehiclePawn)
	{
		/*
		FVector Start = VehiclePawn->GetInternalCameraSceneComponent()->GetComponentLocation() + VehiclePawn->GetInternalCameraSceneComponent()->GetForwardVector() * Range/100;
		FVector End = Start + VehiclePawn->GetInternalCameraSceneComponent()->GetForwardVector() * Range;
	//	FVector End = VehiclePawn->GetActorLocation() + VehiclePawn->GetActorForwardVector() * Range;
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());

		DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")),Damage);

		FTransform MuzzleTransform;
		MuzzleTransform.SetLocation(End + FVector::UpVector * 40);
		//FRotator rot = 
		MuzzleTransform.SetRotation(FRotator(0,0,0).Quaternion());
		MuzzleTransform.SetScale3D(FVector(1.0f));

		FActorSpawnParameters SpawnParamters; 
		SpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
		//ALaserProjectile* Projectile = GetWorld()->SpawnActorDeferred<ALaserProjectile>(LaserProjectileClass, MuzzleTransform, GetOwningActorFromActorInfo(), VehiclePawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		ALaserProjectile* Projectile = GetWorld()->SpawnActor<ALaserProjectile>(LaserProjectileClass, Start, FRotator::ZeroRotator, SpawnParamters);
		Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
		Projectile->Range = Range;
		Projectile->FireInDirection(FVector(0,1,0));
		Projectile->FinishSpawning(MuzzleTransform);

		*/
	}
}
