// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	void SetPawn(APawn* inPawn);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* aimCompRef);
	UFUNCTION()
		void OnPossessedTankDeath();
public:

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float crosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float crosshairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000;
	bool GetLookDirection(FVector2D screenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
