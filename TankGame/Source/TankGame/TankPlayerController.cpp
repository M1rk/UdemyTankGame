// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "string.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	ATank* b = GetControlledTank();
	if (b != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyPlayerTank Name is %s"), *b->GetName());

	}
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

