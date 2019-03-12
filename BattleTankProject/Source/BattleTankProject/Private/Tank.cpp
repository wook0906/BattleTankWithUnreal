// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankProject.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();
	currentHealth = startingHealth;
}
float ATank::TakeDamage(float damageAmount, struct FDamageEvent const & damageEvent, class  AController* eventInstigator, AActor * damageCauser) {
	int32 damagePoints = FPlatformMath::RoundToInt(damageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, currentHealth);
	
	currentHealth -= damageToApply;
	if (currentHealth <= 0) {
		OnDeath.Broadcast();
	}
	return damageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)currentHealth/(float)startingHealth;
}
