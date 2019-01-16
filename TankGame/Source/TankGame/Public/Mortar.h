// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"

UCLASS()
class TANKGAME_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMortar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthProcentage() const;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(EditAnywhere, Category = "Health")
		int32 CurrentHealth;
	
	
};
