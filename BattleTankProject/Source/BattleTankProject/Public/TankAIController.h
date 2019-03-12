// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANKPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Setup")
	float acceptanceRadius = 8000;
private:
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* inPawn) override;
	virtual void Tick(float deltaTime) override;
	UFUNCTION()
		void OnPossessedTankDeath();
};
