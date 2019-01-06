// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	

}
void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); //танк игрока
	auto ControlledTank = Cast<ATank>(GetPawn()); //танк под контролем ИИ
	
	if (ensure(PlayerTank)) 
	{
		//Move toward the player
		MoveToActor(PlayerTank, 300);
		//Aim toward the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//Fire if ready
		ControlledTank->Fire();
	}
}


