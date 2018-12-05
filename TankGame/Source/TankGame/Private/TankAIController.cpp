// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* b = GetControlledTank();
	if (b != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerTank Name is %s"), *b->GetName());
		
	}
	auto pawn = GetPlayerTank();

}
void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("exists!"));
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
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn doesn't exist"));
		return nullptr;

	}
	UE_LOG(LogTemp, Warning, TEXT("We've got PlayerPawn from TankAIController: %s"),*PlayerPawn->GetName());
	return Cast<ATank>(PlayerPawn);
}
