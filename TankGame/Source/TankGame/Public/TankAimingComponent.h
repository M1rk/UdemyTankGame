// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	FVector OutLaunchVelocity;
	UTankAimingComponent();
	void AimAt(FVector HitLocation,float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTurret* TurretToSet);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	TArray<AActor*>ArrayToIgnore;
};
