// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
		virtual void SetPawn(APawn* InPawn) override;
		void BeginPlay() override;
		void Tick(float DeltaTime) override;
		UFUNCTION()
		void OnDeath();
private:

protected:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 10000; //насколько близко будут подъезжать боты 
	
};
