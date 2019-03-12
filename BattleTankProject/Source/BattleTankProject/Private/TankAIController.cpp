// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankProject.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"
void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	/*if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank Find : %s"), *playerTank->GetName());
	}*/
}
void ATankAIController::SetPawn(APawn* inPawn) {
	Super::SetPawn(inPawn);
	if (inPawn) {
		auto possessedTank = Cast<ATank>(inPawn);
		if (!ensure(possessedTank)) { return; }
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}
void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) {
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();
	if (ensure(playerTank && controlledTank)) {
		MoveToActor(playerTank,acceptanceRadius);//centimeter
		auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(playerTank->GetActorLocation());
		if (aimingComponent->GetFiringState() == EFiringState::locked) {
			aimingComponent->Fire();
		}
	}
}





