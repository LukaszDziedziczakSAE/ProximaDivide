// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SurvivalSciFi_GameInstance.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API USurvivalSciFi_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USurvivalScifi_SaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly)
	int MaxSlots = 3;

	UFUNCTION()
	void UpdateMapName();

public:
	UFUNCTION(BlueprintPure)
	USurvivalScifi_SaveGame* GetCurrentSaveGame() { return CurrentSaveGame; }

	UFUNCTION(BlueprintCallable)
	void SaveCurrentGame();

	UFUNCTION(BlueprintCallable)
	bool LoadSlot(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	bool SaveSlot(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	bool DoesSlotExist(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void StartNewGame(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void StartLoadGame(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void SwitchToMap(FName MapName, FName StartTag = "");

	UFUNCTION(BlueprintCallable)
	void OnLevelStart();

	UFUNCTION(BlueprintCallable)
	void DeleteSlot(int SlotNumber);
};
