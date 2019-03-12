// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKPROJECT_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float relativeSpeed);
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDegreesPerSecond = 10;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxElevationDegrees = 40;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float minElevationDegrees = 0;
	
	
};
