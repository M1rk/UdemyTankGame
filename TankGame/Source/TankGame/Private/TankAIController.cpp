// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	

}
void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) 
	{
		//Move toward the player
		//...
		//Aim toward the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		
		//Fire if ready
	}
	
}
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerPawn doesn't exist"));
		return nullptr;

	}
	//UE_LOG(LogTemp, Warning, TEXT("We've got PlayerPawn from TankAIController: %s"),*PlayerPawn->GetName());
	return Cast<ATank>(PlayerPawn);
}
