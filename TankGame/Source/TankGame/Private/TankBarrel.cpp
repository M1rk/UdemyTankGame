// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"



void UTankBarrel::Elevate(float RelativeSpeed) // RelativeSpeed - ������-�� �������� ������������� ������������ �������,� �� ���������
{                                               //��� ������ �������, ������� ��������� � ������� -1 / 1 � ������ ������ �����������
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation,0,0));
	
	
}