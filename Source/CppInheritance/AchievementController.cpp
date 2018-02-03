// Fill out your copyright notice in the Description page of Project Settings.

#include "AchievementController.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"

// Sets default values
AAchievementController::AAchievementController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAchievementController::BeginPlay()
{
	Super::BeginPlay();

	if (KilledCountTextWidget) {
		pKilledCountTextWidget = CreateWidget<UUserWidget>
			(GetGameInstance(), KilledCountTextWidget);

		if (pKilledCountTextWidget.IsValid()) {
			pKilledCountTextWidget->AddToViewport();
			pKilledCountText = (UTextBlock*)pKilledCountTextWidget
				->GetWidgetFromName("TextKilledTypeCount");
		}
	}

	if (FullHealthTextWidget) {
		pFullHealthTextWidget = CreateWidget<UUserWidget>
			(GetGameInstance(), FullHealthTextWidget);

		if (pFullHealthTextWidget.IsValid()) {
			pFullHealthTextWidget->AddToViewport();
			pFullHealthText = (UTextBlock*)pFullHealthTextWidget
				->GetWidgetFromName("TextFullHealthOnFinish");
		}
	}
	
}

FString AAchievementController::
formatKilledCount(TMap<FString, int32> CounterKilledByType) const
{
	FString formatted = "";
	for (auto& Elem : CounterKilledByType) {
		formatted += Elem.Key + " kills: " + FString::FromInt(Elem.Value) + "\n";
	}

	return formatted;
}

// Called every frame
void AAchievementController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAchievementController::setKilledCount(TMap<FString, int32> CounterKilledByType)
{
	FString TextToShow = formatKilledCount(CounterKilledByType);
	if (pKilledCountText.IsValid()) {
		pKilledCountText->SetText(FText::FromString(TextToShow));
	}
}

void AAchievementController::setFullHealth(bool value)
{
	if (pFullHealthText.IsValid()) {
		//pFullHealthText->SetVisibility(ESlateVisibility::Visible);

		FString TextToShow = value ? "No hit by any enemy" : "Hit by enemy at least once";
		pFullHealthText->SetText(FText::FromString(TextToShow));
	}
}

