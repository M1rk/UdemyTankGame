// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
	
}

float ATank::GetHealthProcentage() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints,0,CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp,Warning,TEXT("DamageAmount: %f,DamageToApply: %d,CurrentHealth = %d"),DamageAmount, DamageToApply,CurrentHealth)
		if (CurrentHealth <= 0) 
		{
			OnTankDeath.Broadcast();
		}
	return DamageToApply;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}


