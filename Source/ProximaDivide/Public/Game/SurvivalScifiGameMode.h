// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game/MissionDataAsset.h"
#include "SurvivalScifiGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHourTick);

UCLASS()
class PROXIMADIVIDE_API ASurvivalScifiGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivalScifiGameMode();

protected:
	UPROPERTY(EditAnywhere)
	int Day = 1;

	UPROPERTY(EditAnywhere)
	int Hour = 8;

	UPROPERTY(EditAnywhere)
	float SecondsPerHour = 120;

	UPROPERTY(VisibleAnywhere)
	float SecondsLeftInHour;

	UPROPERTY()
	class USurvivalSciFi_GameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	TMap<FString, UMissionDataAsset*> OnStartGiveMission;

	UPROPERTY(VisibleAnywhere)
	// Add this flag to ensure restoration only happens once
	bool bWorldObjectsRestored = false;

	UPROPERTY(EditAnywhere)
	bool bRestoreObjectsOnStartingNewPlayer;

	UPROPERTY(EditAnywhere)
	bool bRestoreObjectsOnBeginPlay;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	// Override to restore world objects before player pawn is spawned
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	UFUNCTION(BlueprintPure)
	int GetDay() { return Day; }

	UFUNCTION(BlueprintPure)
	int GetHour() { return Hour; }

	UFUNCTION(BlueprintPure)
	int GetSecondsLeftInHour() { return SecondsLeftInHour; }

	UFUNCTION(BlueprintPure)
	float GetTimeProgress();

	UFUNCTION()
	void UpdatePlayerStartTag(FName PlayerStartTag);

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	struct FWorldData GetSaveData();

	UFUNCTION()
	struct FTimeData GetTimeData();

	UFUNCTION()
	void LoadDataFromSave();

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnHourTick OnHourTick;

	UFUNCTION(BlueprintCallable)
	FString GetCurrentMapName();

	UFUNCTION(BlueprintCallable)
	UMissionDataAsset* GetOnStartMission();

	UFUNCTION(BlueprintCallable)
	void PopulateLevelFromData(struct FWorldData Data);
};
