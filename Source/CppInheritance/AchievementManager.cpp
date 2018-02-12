// Fill out your copyright notice in the Description page of Project Settings.

#include "AchievementManager.h"
#include "JumpingShootingSlugEnemy.h"
#include "ShootingSlugEnemy.h"
#include "SuperShootingSlugEnemy.h"
#include "AchievementController.h"

#include "EngineMinimal.h"
#include "EngineUtils.h"

// Sets default values
AAchievementManager::AAchievementManager() :
	FullHealth(true),
	KilledEnemiesCount(0),
	ShotsFired(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize enemy killed counter by type
	CounterKilledByType.Emplace(AJumpingShootingSlugEnemy::TYPE_KEY, 0);
	CounterKilledByType.Emplace(AShootingSlugEnemy::TYPE_KEY, 0);
	CounterKilledByType.Emplace(ASuperShootingSlugEnemy::TYPE_KEY, 0);
}

// Called when the game starts or when spawned
void AAchievementManager::BeginPlay()
{
	Super::BeginPlay();

	FString AchievementCtl = FString(TEXT("AchievementController_1"));
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (AchievementCtl.Equals(ActorItr->GetName()))
		{
			// Conversion to smart pointer 
			AchievementControllerRef = *ActorItr;
			break;
		}
	}
}

// Called every frame
void AAchievementManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAchievementManager::isFullHealth() const
{
	return this->FullHealth;
}

void AAchievementManager::setFullHealth(bool value)
{
	this->FullHealth = value;
}

int AAchievementManager::getKilledByType(FString type) const
{
	if (CounterKilledByType.Contains(type)) 
	{
		// Despite its name returns value copy instead of ref
		return CounterKilledByType.FindRef(type);
	} 
	else 
	{
		return 0;
		//throw new EnemyTypeNotFoundException();
	}
}

void AAchievementManager::incrementKillsByType(FString type)
{
	if (CounterKilledByType.Contains(type))
	{
		this->KilledEnemiesCount ++;
		// Despite its name returns value copy instead of ref
		int32 count = CounterKilledByType.FindRef(type);
		CounterKilledByType.Emplace(type, ++count);

		// Check validity and cast
		if (AchievementControllerRef.IsValid() &&
			AchievementControllerRef.Get()->IsA(AAchievementController::StaticClass()))
		{
			AAchievementController* AchievementControllerPtr =
				Cast<AAchievementController>(AchievementControllerRef.Get());

			AchievementControllerPtr->setKilledCount(CounterKilledByType);
		}
	}
	else
	{
		//throw new EnemyTypeNotFoundException();
	}
}

void AAchievementManager::finish() const
{
	// Check validity and cast
	if (AchievementControllerRef.IsValid() &&
		AchievementControllerRef.Get()->IsA(AAchievementController::StaticClass()))
	{
		AAchievementController* AchievementControllerPtr =
			Cast<AAchievementController>(AchievementControllerRef.Get());

		// Show stats
		AchievementControllerPtr->setMissingShot(this->ShotsFired > this->KilledEnemiesCount);
		AchievementControllerPtr->setFullHealth(this->FullHealth);
	}
}

void AAchievementManager::incrementShotsFired()
{
	this->ShotsFired++;
}

