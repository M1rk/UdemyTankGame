// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
}
UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle) 
{
	
	float CurrentThrottle =FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	DriveTrack(CurrentThrottle);
} 


void UTankTrack::DriveTrack(float CurrentThrottle)
{
	
	auto ForceApplied = CurrentThrottle * TrackMaxDriveForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) 
	{
		Wheel->AddDrivingForce(ForcePerWheel);
		
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels()
{
	TArray<ASprungWheel*> ResultArray;
	TArray <USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		//�� ���� child'�� �������� ������ ��, ��� ����� ��� USpawnPoint
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild)
		{
			continue;
		}
		//� ������� USpawnPoint'a ���� Actor'a (ASprungWheel), ������� ��������� � ��� �����������
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) 
		{
			continue;
		}
		//������� � �������� ������
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}
