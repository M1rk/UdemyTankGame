// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(CollisionMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ImpactBlast->bAutoActivate = false;
	RootComponent = CollisionMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComp"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	OnActorHit.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float LaunchSpeed) 
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*LaunchSpeed);
	
	
	ProjectileMovement->Activate();
}
void  AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor,FVector NormalImpulse,
	const FHitResult& Hit)
{
	//UE_LOG(LogTemp,Warning,TEXT("Collide with %s at %s"),*OtherActor->GetName(),*Hit.ToString())
	LaunchBlast->Deactivate();
	ExplosionForce->FireImpulse();
	ImpactBlast->Activate();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	UGameplayStatics::ApplyRadialDamage //метод для нанесения урона от взрыва
	(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);

	FTimerHandle TimerHandle;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);//таймер до уничтожения
	
}
void AProjectile::OnTimerExpire()
{
	Destroy();
}