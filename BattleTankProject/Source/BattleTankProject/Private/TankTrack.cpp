// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankProject.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}
void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit) {
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}
void UTankTrack::ApplySidewaysForce() {
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto deltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForece = tankRoot->GetMass() * correctionAcceleration / 2;
	tankRoot->AddForce(correctionForece);
}
void UTankTrack::SetThrottle(float throttle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle+throttle,-1,1);
}
void UTankTrack::DriveTrack() {
	auto forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, ForceLocation);
}

