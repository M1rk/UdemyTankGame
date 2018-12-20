// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	ATank* GetControlledTank();
	virtual void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	FHitResult GetLookVectorHitLocation(FVector CameraWorldLocation, FVector LookDirection);
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(OUT FVector &HitLocation);
	bool GetLookDirection(FVector2D ScreenLocation, FVector & WorldDirection, FVector &CameraWorldLocation);
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333f;
};
