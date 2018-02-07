// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AchievementController.generated.h"

UCLASS()
class CPPINHERITANCE_API AAchievementController : public AActor
{
	GENERATED_BODY()
	// TextKilledTypeCount
	// TextNoMissingShot
	// TextFullHealthOnFinish

public:	
	// Sets default values for this actor's properties
	AAchievementController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> KilledCountTextWidget;
	TWeakObjectPtr<class UUserWidget> pKilledCountTextWidget;
	TWeakObjectPtr<class UTextBlock> pKilledCountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> FullHealthTextWidget;
	TWeakObjectPtr<class UUserWidget> pFullHealthTextWidget;
	TWeakObjectPtr<class UTextBlock> pFullHealthText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> MissedShotTextWidget;
	TWeakObjectPtr<class UUserWidget> pMissedShotTextWidget;
	TWeakObjectPtr<class UTextBlock> pMissedShotText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FString formatKilledCount(TMap<FString, int32> CounterKilledByType) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void setKilledCount(TMap<FString, int32> CounterKilledByType);
	void setFullHealth(bool value);
	void setMissingShot(bool value);
};
