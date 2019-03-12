// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKPROJECT_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float throwVal);
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float throwVal);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Init(UTankTrack* L, UTankTrack* R);

private:
	virtual void RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;
};
