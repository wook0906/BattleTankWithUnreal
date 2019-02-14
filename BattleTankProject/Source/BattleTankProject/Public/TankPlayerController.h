// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;

	UPROPERTY(EditAnywhere)
		float crosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float crosshairYLocation = 0.33333f;
};
