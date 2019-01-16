// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Tank.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);


	
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel= CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraint();

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;   //каждый кадр обнуляем составляющую силы воздействия
	}

}
void ASprungWheel::SetupConstraint()
{
	if (GetAttachParentActor())
	{
		UStaticMeshComponent* TankBody = nullptr;
		TArray<UStaticMeshComponent*> StaticComps;
		GetAttachParentActor()->GetComponents<UStaticMeshComponent>(StaticComps);

		if (StaticComps.Num()>0)
		{
			for (auto Component : StaticComps)
			{
				if (Component->GetName() == "TankBody")
				{
					TankBody = Component;
				}
			}
			if (TankBody)
			{
				MassWheelConstraint->SetConstrainedComponents(TankBody, NAME_None, Axle, NAME_None);
				AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
				
			}
		}

	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}
void ASprungWheel::ApplyForce()
{

	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();//сила приложена всегда, когда ASprungWheel чего-то касается, но вот размер силы определается вводом wasd через Clamp(-1,1)
}

