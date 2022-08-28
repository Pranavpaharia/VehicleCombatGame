// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/LaserProjectile.h"

// Sets default values
ALaserProjectile::ALaserProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	NetUpdateFrequency = 100;
	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(FName("CollisionComponent"));
	SetRootComponent(ProjectileCollisionComponent);

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetupAttachment(ProjectileCollisionComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(ProjectileCollisionComponent);

}

// Called when the game starts or when spawned
void ALaserProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	
}

