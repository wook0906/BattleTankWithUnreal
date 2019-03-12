// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8{
	reloading,aiming,locked,OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	void AimAt(FVector hitLocation);
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Init(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRoundsLeft() const;
protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringState firingState = EFiringState::reloading;
private:
	UTankAimingComponent();
	virtual void TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction) override;

	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector aimDirection);
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float launchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> projectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float reloadTimeInSeconds = 3;
	double lastFireTime = 0;

	bool IsBarrelMoving();
	FVector aimDirection;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 roundsLeft = 3;
};
