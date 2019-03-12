// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankProject.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Init(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {
	
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}
void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed) {
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = moveVelocity.GetSafeNormal();
	auto forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	IntendMoveForward(forwardThrow);
	auto rightThrow = FVector::CrossProduct(tankForward,aiForwardIntention).Z;
	IntendTurnRight(rightThrow);
	//UE_LOG(LogTemp,Warning,TEXT("%s vectoring to %s"),*tankName,*moveVelocityString)
}
void UTankMovementComponent::IntendMoveForward(float throwVal) {
	if (!ensure(leftTrack || !rightTrack)) {
		return;
	}
	leftTrack->SetThrottle(throwVal);
	rightTrack->SetThrottle(throwVal);
}
void UTankMovementComponent::IntendTurnRight(float throwVal) {
	if (!ensure(leftTrack || !rightTrack)) {
		return;
	}
	leftTrack->SetThrottle(throwVal);
	rightTrack->SetThrottle(-throwVal);
}
