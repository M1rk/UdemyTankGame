// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class UTankAimingComponent;
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	FHitResult GetLookVectorHitLocation(FVector CameraWorldLocation, FVector LookDirection);
	void AimTowardsCrosshair();
	UFUNCTION()
	void OnDeath();
	bool GetSightRayHitLocation(OUT FVector &HitLocation);
	bool GetLookDirection(FVector2D ScreenLocation, FVector & WorldDirection, FVector &CameraWorldLocation);
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333f;
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);//סמבûעטו, גûחûגאועסÿ ג ÁÏ?
	virtual void SetPawn(APawn* InPawn) override;
	
};
