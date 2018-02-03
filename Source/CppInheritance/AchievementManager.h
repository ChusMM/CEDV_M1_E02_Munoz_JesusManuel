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
	TMap<FString, int32> CounterKilledByType;
	bool FullHealth;
	bool MissingShot;

	TWeakObjectPtr<AActor> AchievementControllerRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool isFullHealth() const;

	UFUNCTION(BlueprintCallable, Category = "AchievementManager")
	void setFullHealth(bool value);
	
	bool hasMissedAnyShot() const;
	void setMissingShot(bool value);

	int getKilledByType(FString type) const;
	void incrementKillsByType(FString type);
};
