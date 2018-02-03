#include "ShootingSlugEnemy.h"
#include "EngineMinimal.h"

const FString AShootingSlugEnemy::TYPE_KEY = "shooting";

// Sets default values
// Invoke the parent constructor in the initialization list
AShootingSlugEnemy::AShootingSlugEnemy() : Super()
{
	// Set enemy type in super class
	setType(TYPE_KEY);
}

void AShootingSlugEnemy::RunBehaviour()
{
	// If fire interval has elapsed, spawn a new enemy projectile
	if (AccumulatedDeltaTime >= FireTimeInterval) {
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 250.0f;
		FRotator SpawnRotation = GetActorRotation();

		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);

		AccumulatedDeltaTime = 0.0f;
	}
}
