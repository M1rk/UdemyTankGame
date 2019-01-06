// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	

}
void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); //танк игрока
	auto ControlledTank = GetPawn(); //танк под контролем ИИ
	
	if (!ensure(PlayerTank&&ControlledTank)) { return; }
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	//Move toward the player
	MoveToActor(PlayerTank, 1);
	//Aim toward the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//Fire if ready
	//AimingComponent->Fire();
	
}


