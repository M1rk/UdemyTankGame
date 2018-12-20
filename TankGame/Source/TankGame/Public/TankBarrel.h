// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	UPROPERTY(EditAnywhere,Category = Setup)
	float MaxDegreesPerSecond = 10.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 30.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = -30.0f;
};

