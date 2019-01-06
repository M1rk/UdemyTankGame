// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	OutLaunchVelocity = FVector(0, 0, 0);
	// ...
	ArrayToIgnore.Add(GetOwner());
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds)
	{
		Firingstate = EFiringState::Locked;
	}
	// ...
}
void UTankAimingComponent::AimAt(FVector HitLocation) 
{
	
	if (!ensure(Barrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel was not found"));
		return;
	}
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));//позиция сокета на конце пушки
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,// OUT parameter даёт нам выходной вектор
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ArrayToIgnore,
		false

	);
	
	if (bHaveAimSolution) 
	{
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveBarrelTowards(AimDirection); //двигаем пушку по вертикали так, чтобы при выстреле с заданными параметрами снаряд попал туда, куда указывает прицел
	MoveTurretTowards(AimDirection);//двигаем башню по горизонтали так, чтобы при выстреле с заданными параметрами снаряд попал туда, куда указывает прицел
	
	}
	else 
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Solution was NOT found"), Time)
	}
	
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { 
		
		return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	
	
	

}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)// поднимаем/опускаем ствол пушки
{
	if (!ensure(Barrel) || !ensure(Turret)) {return;}
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();//куда смотрит пушка
	auto AimAsRotator = AimDirection.Rotation();//куда мы хотим попасть после выстрела
	auto DeltaRotator = AimAsRotator - BarrelRotator;//разница, которую передаём в метод Elevate (-1 или +1 после Clamp)
	
	Barrel->Elevate(DeltaRotator.Pitch);
	
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) //вращаем башню
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //куда смотрит пушка
	auto AimAsRotator = AimDirection.Rotation(); //куда мы хотим попасть после выстрела
	auto DeltaRotator = AimAsRotator - BarrelRotator; //разница, которую передаём в метод Turn (-1 или +1 после Clamp)
	Turret->Turn(DeltaRotator.Yaw);
}
void UTankAimingComponent::Fire() 
{
	if (!ensure(Barrel&&ProjectileBluePrint)) { return; }
	 //текущее время с начала игры минус время последнего выстрела
	 //сравниваем со временем перезарядки
	if (Firingstate != EFiringState::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Firingstate = EFiringState::Reloading;

	}
}
