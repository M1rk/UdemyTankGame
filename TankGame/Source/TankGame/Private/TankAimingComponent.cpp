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
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));//������� ������ �� ����� �����
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,// OUT parameter ��� ��� �������� ������
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
	MoveBarrelTowards(AimDirection); //������� ����� �� ��������� ���, ����� ��� �������� � ��������� ����������� ������ ����� ����, ���� ��������� ������
	MoveTurretTowards(AimDirection);//������� ����� �� ����������� ���, ����� ��� �������� � ��������� ����������� ������ ����� ����, ���� ��������� ������
	
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
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)// ���������/�������� ����� �����
{
	if (!ensure(Barrel) || !ensure(Turret)) {return;}
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();//���� ������� �����
	auto AimAsRotator = AimDirection.Rotation();//���� �� ����� ������� ����� ��������
	auto DeltaRotator = AimAsRotator - BarrelRotator;//�������, ������� ������� � ����� Elevate (-1 ��� +1 ����� Clamp)
	
	Barrel->Elevate(DeltaRotator.Pitch);
	
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) //������� �����
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //���� ������� �����
	auto AimAsRotator = AimDirection.Rotation(); //���� �� ����� ������� ����� ��������
	auto DeltaRotator = AimAsRotator - BarrelRotator; //�������, ������� ������� � ����� Turn (-1 ��� +1 ����� Clamp)
	Turret->Turn(DeltaRotator.Yaw);
}
void UTankAimingComponent::Fire() 
{
	if (!ensure(Barrel&&ProjectileBluePrint)) { return; }
	 //������� ����� � ������ ���� ����� ����� ���������� ��������
	 //���������� �� �������� �����������
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
