// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankProject.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}
void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
		auto controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing : %s"), *controlledTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}
void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction : %s"), *hitLocation.ToString());
	}
	
}
bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const {
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX,viewportSizeY);
	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *screenLocation.ToString());
	return true;
}
