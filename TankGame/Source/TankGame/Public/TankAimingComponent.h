// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state:
UENUM()
enum class EFiringState : uint8
{
	Locked,
    Aiming,
    Reloading
};

class UTurret;
class UTankBarrel;
class AProjectile;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	FVector OutLaunchVelocity;
	UTankAimingComponent();
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Firing")
	int32 AmmoCount = 10;
	EFiringState GetFiringState();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EFiringState Firingstate = EFiringState::Locked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float ReloadTimeInSeconds = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 50000;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	bool isBarrelMoving();
	TArray<AActor*>ArrayToIgnore;
	double LastFireTime = 0;
	FVector AimDirection;
};
