/*********************************************************************
* Module 1. Programming Foundations
* Author: David Vallejo Fern�ndez    David.Vallejo@uclm.es
*         Santiago S�nchez Sobrino   Santiago.Sanchez@uclm.es
*
* You can redistribute and/or modify this file under the terms of the
* GNU General Public License ad published by the Free Software
* Foundation, either version 3 of the License, or (at your option)
* and later version. See <http://www.gnu.org/licenses/>.
*
* This file is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class ABaseEnemy;


UCLASS()
class CPPINHERITANCE_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyManager();

	// Enemies limit can be set up from editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemiesLimit")
	int32 EnemiesLimit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Temporal reference to spawn new enemies
	float AccumulatedDeltaTime;
	float EnemySpawnTimeSeconds;
	int EnemiesSpawned;

	// Keeps a list of enemy types to spawn
	TArray<TSubclassOf<ABaseEnemy>> EnemyClasses;

	// Invisible plane to spawn enemies
	TWeakObjectPtr<AActor> ReferencePlane;

	int GetNumberOfEnemies() const;
	FVector GetRandomLocationFromReferencePlane() const;
	TSubclassOf<ABaseEnemy> GetRandomEnemyClass() const;
	void SpawnEnemy();

	// Reference to AchieveManager to notify finish game in order to show the stats
	TWeakObjectPtr<AActor> ReferenceAchievementMan;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
