// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FTankDelegate OnTankDeath;

	UFUNCTION(BlueprintPure,Category = "Health")
	float GetHealthProcentage() const;
	//called when actor damage is dealt
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere,Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(EditAnywhere, Category = "Health")
		int32 CurrentHealth;

	
};
