// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
void UTurret::Turn(float RelativeTurnSpeed) 
{
	RelativeTurnSpeed = FMath::Clamp<float>(RelativeTurnSpeed, -1, 1);
	auto TurnChange = RelativeTurnSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewTurn = RelativeRotation.Yaw + TurnChange;
	
	SetRelativeRotation(FRotator(0, RawNewTurn, 0));
}
