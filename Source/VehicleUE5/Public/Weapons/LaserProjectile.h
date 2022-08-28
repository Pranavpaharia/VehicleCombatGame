// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "LaserProjectile.generated.h"

UCLASS()
class VEHICLEUE5_API ALaserProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserProjectile();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USphereComponent* ProjectileCollisionComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FHitResult ProjectileHitResult;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE FGameplayEffectSpecHandle GetDamageEffectSpecHandle() const { return DamageEffectSpecHandle; };

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE FHitResult GetProjectileHitResult() const { return ProjectileHitResult; };
};
