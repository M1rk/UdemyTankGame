// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendMoveBackward(float Throw) 
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw) 
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	float dotproduct = FVector::DotProduct(TankForward, AIForwardIntention);
	float crossproductABS = FVector::CrossProduct(TankForward, AIForwardIntention).Size();
	if (crossproductABS > 0) 
	{
	//IntendTurnRight(crossproductABS);
	}
	else 
	{
	//IntendTurnLeft(crossproductABS);

	}
	
	FRotator TankRotation = GetOwner()->GetActorRotation();
	FRotator MoveVelocityRotation = MoveVelocity.ToOrientationRotator();
	auto RotationDifferenceYaw = FMath::Clamp((MoveVelocityRotation - TankRotation).Yaw, -1.0f, 1.0f);
	auto RotationChangeYaw = RotationDifferenceYaw * 30 * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotationYaw = GetOwner()->GetActorRotation().Yaw + RotationChangeYaw;
	GetOwner()->SetActorRotation(FRotator(TankRotation.Pitch, RawNewRotationYaw, TankRotation.Roll));
	 //моя версия решения проблемы поворота. в курсе предлагается использовать CrossProduct + методы IntendTurnRight/Left

	
	//IntendMoveForward(dotproduct);
	
}