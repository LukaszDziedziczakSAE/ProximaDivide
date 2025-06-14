// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Enviroment/EEnviroment.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "Game/MapStartDataStruct.h"
#include "SurvivalSciFi_GameInstance.generated.h"

UCLASS()
class PROXIMADIVIDE_API USurvivalSciFi_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifi_SaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly)
	int MaxSlots = 3;

	UFUNCTION()
	void UpdateMapName();

	UPROPERTY(EditAnywhere)
	class UAkAudioEvent* Ambience;

	UPROPERTY(EditAnywhere)
	UAkAudioEvent* Music;

	UPROPERTY(EditDefaultsOnly)
	class UAkStateValue* MenuState;

	UPROPERTY(EditDefaultsOnly)
	UAkStateValue* DecentCinematicState;

	UPROPERTY(EditDefaultsOnly)
	UAkStateValue* ShipState;

	UPROPERTY(EditDefaultsOnly)
	UAkStateValue* InsideState;

	UPROPERTY(EditDefaultsOnly)
	UAkStateValue* OutsideState;

	UPROPERTY(EditDefaultsOnly)
	UAkStateValue* PostCrashState;

	UPROPERTY(VisibleAnywhere)
	bool bMusicAndAmbience;

	UFUNCTION()
	void LoadCurrentSaveMap();

	UPROPERTY(EditDefaultsOnly, Category = "New Game")
	struct FPlayerData InitialPlayerData;

	UPROPERTY(EditDefaultsOnly, Category = "New Game")
	struct FTimeData InitialTimeData;

	UPROPERTY(EditDefaultsOnly, Category = "New Game")
	EEnviroment InitialEnviroment = EEnviroment::Ship;

	UPROPERTY(EditDefaultsOnly, Category = "New Game")
	FName InitialLevelName = TEXT("L_Ship");

	UPROPERTY(EditDefaultsOnly, Category = "New Game")
	FName InitialPlayerStartTag = TEXT("");

	UPROPERTY(EditDefaultsOnly, Category = "Skip Intro Game")
	struct FPlayerData SkipIntroPlayerData;

	UPROPERTY(EditDefaultsOnly, Category = "Skip Intro Game")
	struct FTimeData SkipIntroTimeData;

	UPROPERTY(EditDefaultsOnly, Category = "Skip Intro Game")
	EEnviroment SkipIntroEnviroment = EEnviroment::Ship;

	UPROPERTY(EditDefaultsOnly, Category = "Skip Intro Game")
	FName SkipIntroLevelName = TEXT("L_Ship");

	UPROPERTY(EditDefaultsOnly, Category = "Skip Intro Game")
	FName SkipIntroPlayerStartTag = TEXT("");

public:
	UFUNCTION(BlueprintPure)
	USurvivalScifi_SaveGame* GetCurrentSaveGame();

	UFUNCTION(BlueprintPure)
	FName GetCurrentMapName() const;

	UFUNCTION(BlueprintCallable)
	FWorldData GetCurrentMapData();

	UFUNCTION(BlueprintCallable)
	FMapStartData GetCurrentMapStartData() const;

	UFUNCTION(BlueprintPure)
	bool HasMapDataForCurrentMap() const;

	UFUNCTION(BlueprintCallable)
	void SaveCurrentGame(int AdvanceHours = 0, bool bIsExitSave = false);

	UFUNCTION(BlueprintCallable)
	bool LoadSlot(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	bool SaveSlot(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	bool DoesSlotExist(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void StartNewGame(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void StartSkipIntroGame(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void StartLoadGame(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void SwitchToMap(FName MapName, FName StartTag = "");

	UFUNCTION(BlueprintCallable)
	void OnLevelStart();

	UFUNCTION(BlueprintCallable)
	void DeleteSlot(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	void PlayMusicAndAmbience();

	UFUNCTION(BlueprintCallable)
	void SetEnviroment(EEnviroment Enviroment);

	UFUNCTION(BlueprintCallable)
	void StartWakeFromSleep(int HoursToSleep, FName PlayerStartTag);

	UFUNCTION(BlueprintCallable)
	void StartRespawn();

	/** Streams in a level by name and restores save data after load. */
	UFUNCTION(BlueprintCallable)
	void StreamInLevelAndRestore(FName LevelName);

	/** Called when the streamed level is fully loaded and visible. */
	UFUNCTION()
	void OnLevelStreamedIn();

	/** Restores all objects (airlocks, items, containers, etc.) from save data for the current map. */
	void RestoreLevelObjects();

	UPROPERTY(VisibleAnywhere)
	bool bLevelSwitchInProgress = false;

	UFUNCTION()
	void SaveAndExitGame();
};
