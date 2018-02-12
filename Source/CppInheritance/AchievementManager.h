// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AchievementManager.generated.h"

UCLASS()
class CPPINHERITANCE_API AAchievementManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAchievementManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Container to store enemies killings by type
	// This can be done thanks to every enemy type has a String type
	TMap<FString, int32> CounterKilledByType;
	
	// To know if player has been hit at least once
	bool FullHealth;
	
	// All types enemies count
	int KilledEnemiesCount;
	
	// Shots fired, so we can know if there are missed shots
	int ShotsFired;

	// Reference to controler in order to control the widgets
	TWeakObjectPtr<AActor> AchievementControllerRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool isFullHealth() const;

	// If we recieve shots, it must be callable from blueprint
	UFUNCTION(BlueprintCallable, Category = "Health")
	void setFullHealth(bool value);

	// Get current killings by type
	int getKilledByType(FString type) const;

	// Increment kills of an especific type
	void incrementKillsByType(FString type);
	
	// We increment shots fired from FirstPersonBP
	UFUNCTION(BlueprintCallable, Category = "Shots")
	void incrementShotsFired();

	// Called when game finish, so we show game stats
	void finish() const;
};
