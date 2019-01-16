// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	

}
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) 
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }
		PossesedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
	}
}
void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); //танк игрока
	auto ControlledTank = GetPawn(); //танк под контролем ИИ
	
	if (!(PlayerTank&&ControlledTank)) { return; }
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	//Move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	//Aim toward the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//Fire if ready
	if (AimingComponent->GetFiringState() != EFiringState::Reloading)
	{
		AimingComponent->Fire();
	}
}
void ATankAIController::OnDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

