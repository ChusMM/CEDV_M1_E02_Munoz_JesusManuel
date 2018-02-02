#include "EnemyManager.h"
#include "EngineUtils.h"

#include "ShootingSlugEnemy.h"
#include "JumpingShootingSlugEnemy.h"
#include "SuperShootingSlugEnemy.h"


// Example of member initialization list
AEnemyManager::AEnemyManager() : 
	AccumulatedDeltaTime(0.0f), 
	EnemySpawnTimeSeconds(3.5f), 
	MaxNumberOfEnemies(5), 
	ReferencePlane(0) 
{
	PrimaryActorTick.bCanEverTick = true;

	// Store references to enemy classes for later
	EnemyClasses.AddUnique(AShootingSlugEnemy::StaticClass());
	EnemyClasses.AddUnique(AJumpingShootingSlugEnemy::StaticClass());
	EnemyClasses.AddUnique(ASuperShootingSlugEnemy::StaticClass());
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	FString EnemySpawnPlaneString = FString(TEXT("EnemySpawnPlane"));

	// Get a reference to the invisible plane used to spawn enemies
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (EnemySpawnPlaneString.Equals(ActorItr->GetName()))
		{
			// Conversion to smart pointer
			ReferencePlane = *ActorItr;
			break;
		}
	}
}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;
	if ((AccumulatedDeltaTime >= EnemySpawnTimeSeconds)
		&&
		(GetNumberOfEnemies() < MaxNumberOfEnemies))
	{
		// Spawn new enemy and reset the counter
		SpawnEnemy();
		AccumulatedDeltaTime = 0.0f;
	}
}

int AEnemyManager::GetNumberOfEnemies() const
{
	int LivingEnemies = 0;

	for (TActorIterator<ABaseEnemy> ActorItr(GetWorld(), ABaseEnemy::StaticClass()); 
		ActorItr; ++ActorItr)
	{
		LivingEnemies++;
	}

	return LivingEnemies;
}

FVector AEnemyManager::GetRandomLocationFromReferencePlane() const
{
	FVector RandomLocation;
	FVector Orgin;
	FVector BoundsExtent;
	ReferencePlane->GetActorBounds(false, Orgin, BoundsExtent);

	// Build a bounding box and get a random location.
	RandomLocation = FMath::RandPointInBox(FBox::BuildAABB(Orgin, BoundsExtent));

	return RandomLocation;
}

TSubclassOf<ABaseEnemy> AEnemyManager::GetRandomEnemyClass() const
{
	return EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
}

void AEnemyManager::SpawnEnemy()
{
	TSubclassOf<ABaseEnemy> EnemyType = GetRandomEnemyClass();
	FVector EnemySpawnLocation = GetRandomLocationFromReferencePlane();
	GetWorld()->SpawnActor(EnemyType, &EnemySpawnLocation);
}
