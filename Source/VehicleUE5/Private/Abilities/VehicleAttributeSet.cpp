// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/VehicleAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "VehicleUE5Pawn.h"
#include "VehiclePlayerController.h"

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
	DOREPLIFETIME(UVehicleAttributeSet, Damage);

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

void UVehicleAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVehicleAttributeSet, Damage, OldValue);
}

void UVehicleAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		
	}
}

void UVehicleAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AVehicleUE5Pawn* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AVehicleUE5Pawn>(TargetActor);
	}

	// Get the Source actor
	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	AVehicleUE5Pawn* SourceCharacter = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}

		// Use the controller to find the source pawn
		if (SourceController)
		{
			SourceCharacter = Cast<AVehicleUE5Pawn>(SourceController->GetPawn());
		}
		else
		{
			SourceCharacter = Cast<AVehicleUE5Pawn>(SourceActor);
		}

		// Set the causer actor based on context if it's set
		if (Context.GetEffectCauser())
		{
			SourceActor = Context.GetEffectCauser();
		}

		if (Data.EvaluatedData.Attribute == GetDamageAttribute())
		{
			// Try to extract a hit result
			FHitResult HitResult;
			if (Context.GetHitResult())
			{
				HitResult = *Context.GetHitResult();
			}

			// Store a local copy of the amount of damage done and clear the damage attribute
			const float LocalDamageDone = GetDamage();
			SetDamage(0.f);

			if (LocalDamageDone > 0.0f)
			{
				// If character was alive before damage is added, handle damage
				// This prevents damage being added to dead things and replaying death animations
				bool WasAlive = true;

				if (TargetCharacter)
				{
					WasAlive = TargetCharacter->IsAlive();
				}

				if (!TargetCharacter->IsAlive())
				{
					//UE_LOG(LogTemp, Warning, TEXT("%s() %s is NOT alive when receiving damage"), TEXT(__FUNCTION__), *TargetCharacter->GetName());
				}

				// Apply the health change and then clamp it
				const float NewHealth = GetHealth() - LocalDamageDone;
				SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

				if (TargetCharacter && WasAlive)
				{
					// This is the log statement for damage received. Turned off for live games.
					//UE_LOG(LogTemp, Log, TEXT("%s() %s Damage Received: %f"), TEXT(__FUNCTION__), *GetOwningActor()->GetName(), LocalDamageDone);

					

					// Show damage number for the Source player unless it was self damage
					if (SourceActor != TargetActor)
					{
						AVehiclePlayerController* PC = Cast<AVehiclePlayerController>(SourceController);
						if (PC)
						{
							PC->ShowDamageNumber(LocalDamageDone, TargetCharacter);
						}
					}
				}
			}
		}
	
		else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			// Handle other health changes.
			// Health loss should go through Damage.
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		} // Health
		else if (Data.EvaluatedData.Attribute == GetNitroManaAttribute())
		{
			// Handle mana changes.
			SetNitroMana(FMath::Clamp(GetNitroMana(), 0.0f, GetNitroMaxMana()));
		} // Mana
		
	}
}