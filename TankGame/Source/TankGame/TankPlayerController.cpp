
// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "string.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
	
	
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}





void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}

	
}



bool ATankPlayerController::GetSightRayHitLocation(OUT FVector &HitLocation)
{
	//позиция прицела в экранных координатах
	int32 ViewportSizeX, ViewportSizeY;
	FVector2D ScreenLocation;
	FVector LookDirection;
	FVector CameraWorldLocation;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	ScreenLocation.X = ViewportSizeX*CrossHairXLocation;
	ScreenLocation.Y = ViewportSizeY*CrossHairYLocation;
	if (GetLookDirection(ScreenLocation, LookDirection,CameraWorldLocation)) 
	{
		
	    FHitResult HitResult = GetLookVectorHitLocation(CameraWorldLocation, LookDirection);
		if (HitResult.Actor!=nullptr) 
		{
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp,Warning,TEXT("Hit Coordinates: %s"),*HitResult.Location.ToString());
	 	//UE_LOG(LogTemp, Warning, TEXT("Hit Distance: %f"), HitResult.Distance);
	 	//UE_LOG(LogTemp, Warning, TEXT("Hit object: %s"), *Cast<AActor>(HitResult.Actor)->GetName());
		}
		
	}
	return true;
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection, FVector &CameraWorldLocation)
{
	
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	return true;
}
FHitResult ATankPlayerController::GetLookVectorHitLocation(FVector CameraWorldLocation,FVector LookDirection) 
{
		FHitResult HitResult(ForceInit);
		FCollisionQueryParams Params= FCollisionQueryParams(FName(TEXT("AimRay")), true,GetPawn()); //GetPawn() позволяет игнорировать свой танк при прицеливании
		//Params.AddIgnoredActor(GetControlledTank());  //так тоже можно игнорировать
		GetWorld()->LineTraceSingleByChannel(HitResult, CameraWorldLocation, CameraWorldLocation + LookDirection * 150000, ECC_Visibility, Params);
		return HitResult;
}
