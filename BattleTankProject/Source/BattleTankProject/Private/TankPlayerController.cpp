// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTankProject.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}
void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) {
		return;
	}
	FoundAimingComponent(aimingComponent);
}
void ATankPlayerController::SetPawn(APawn* inPawn) {
	Super::SetPawn(inPawn);
	if (inPawn) {
		auto possessedTank = Cast<ATank>(inPawn);
		if (!ensure(possessedTank)) { return; }
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}
void ATankPlayerController::OnPossessedTankDeath(){
	StartSpectatingOnly();
}
void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	 auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	 if (!ensure(aimingComponent)) {
		 return;
	 }
	FVector hitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(hitLocation);
	if (bGotHitLocation) {
		aimingComponent->AimAt(hitLocation);
	}
	
}
bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const {
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);

	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection)) {
		return GetLookVectorHitLocation(lookDirection, hitLocation);
	}
	return false;
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection*lineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		//ECollisionChannel::ECC_Visibility
		ECollisionChannel::ECC_Camera)
		) 
	{

		hitLocation = hitResult.Location;
		return true;
	}

	hitLocation = FVector(0);
	return false;
}
bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const {
	FVector cameraWorldLocation;

	return DeprojectScreenPositionToWorld(
		screenLocation.X,
		screenLocation.Y,
		cameraWorldLocation,
		lookDirection);
}

