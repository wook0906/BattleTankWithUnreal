// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKPROJECT_API ATank : public APawn
{
	GENERATED_BODY()
	// Sets default values for this pawn's properties
	
public:
		ATank();
		virtual float TakeDamage(float damageAmount, struct FDamageEvent const & damageEvent, class  AController* eventInstigator, AActor * damageCauser) override;
		UFUNCTION(BlueprintPure,Category = "Health")
		float GetHealthPercent() const;

		FTankDelegate OnDeath;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 startingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 currentHealth;
	virtual void BeginPlay() override;
};
