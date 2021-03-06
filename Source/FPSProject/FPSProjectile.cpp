// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProjectile.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Use a sphere as a simple collison representation.
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
    // Set the sphere's collision radius.
    CollisionComponent->InitSphereRadius(15.f);    
    CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit); // New
    // Set the root component to be collison component.
    RootComponent = CollisionComponent;    

    /* Projectile movement setup */
    /* Experiment on these once projectile starts working */
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = 3000.f;
    ProjectileMovementComponent->MaxSpeed = 3000.f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 0.3f;
    /* /Experiment on these once projectile starts working */

    // Die after 3 seconds
    InitialLifeSpan = 3.f;
}



// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFPSProjectile::FireInDirection(const FVector & ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}


// New
void AFPSProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
    if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    {
        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.f, Hit.ImpactPoint);
    }
}

    