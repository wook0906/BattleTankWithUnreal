// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankProject.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
void UTankAimingComponent::BeginPlay() {
	lastFireTime = FPlatformTime::Seconds();
}
void UTankAimingComponent::TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction) {
	if (roundsLeft <= 0) {
		firingState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds) {
		firingState = EFiringState::reloading;
	}
	else if (IsBarrelMoving()) {
		firingState = EFiringState::aiming;
	}
	else {
		firingState = EFiringState::locked;
	}
}
int32 UTankAimingComponent::GetRoundsLeft() const
{
	return roundsLeft;
}
EFiringState UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

void UTankAimingComponent::Init(UTankBarrel* barrelToSet, UTankTurret* turretToSet) {
	barrel = barrelToSet;
	turret = turretToSet;
}


bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(barrel)) { return false; }
	auto barrelForward = barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01);
}
void UTankAimingComponent::AimAt(FVector hitLocation) {
	if (!ensure(barrel)) { return; }
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			outLaunchVelocity,
			startLocation,
			hitLocation,
			launchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	if(bHaveAimSolution){
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);

	}
	else {
		//no aim solution
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	if (!ensure(barrel) || !ensure(turret)) { return; }
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;
	barrel->Elevate(deltaRotator.Pitch);
	if (FMath::Abs(deltaRotator.Yaw) < 180) {
		turret->Rotate(deltaRotator.Yaw);
	}
	else {
		turret->Rotate(-deltaRotator.Yaw);
	}
}
void UTankAimingComponent::Fire() {
	if (firingState==EFiringState::locked || firingState == EFiringState::aiming) {
		if (!ensure(barrel)) { return; }
		if (!ensure(projectileBlueprint)) { return; }
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
		roundsLeft--;
	}
}

