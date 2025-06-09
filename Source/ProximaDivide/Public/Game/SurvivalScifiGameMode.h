// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	int Hour = 9;

	UPROPERTY(EditAnywhere)
	float SecondsPerHour = 120;

	UPROPERTY(VisibleAnywhere)
	float SecondsLeftInHour;

	UPROPERTY()
	class USurvivalSciFi_GameInstance* GameInstance;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
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
	void LoadDataFromSave();

	UFUNCTION()
	void LoadGame(int SlotNumber = -1);

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnHourTick OnHourTick;
};
