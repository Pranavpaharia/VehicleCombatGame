// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "VehicleAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)


UCLASS()
class VEHICLEUE5_API UVehicleAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:
	UVehicleAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UVehicleAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UVehicleAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Nitro", ReplicatedUsing = OnRep_NitroMana)
	FGameplayAttributeData NitroMana;
	ATTRIBUTE_ACCESSORS(UVehicleAttributeSet, NitroMana)

	UPROPERTY(BlueprintReadOnly, Category = "Nitro", ReplicatedUsing = OnRep_NitroMaxMana)
	FGameplayAttributeData NitroMaxMana;
	ATTRIBUTE_ACCESSORS(UVehicleAttributeSet, NitroMaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Damage" , ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UVehicleAttributeSet, Damage)


protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_NitroMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_NitroMaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);



};
