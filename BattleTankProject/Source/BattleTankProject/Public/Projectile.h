// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LaunchProjectile(float speed);
private:
	UProjectileMovementComponent* projectileMovement = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* collisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* launchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* impactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* explosionForce = nullptr;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit);
	void OnTimerExpire();
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float projectileDamage = 20.f;
};