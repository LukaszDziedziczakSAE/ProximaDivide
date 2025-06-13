// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Enviroment/EEnviroment.h"
#include "Game/MissionStructs.h"
#include "Enviroment/Door/Airlock.h"
#include "Character/Components/PaperdollComponent.h"
#include "Item/Inventory/FInventoryItem.h"
#include "SurvivalScifi_SaveGame.generated.h"

USTRUCT(BlueprintType)
struct FTutorialState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SeenInventoryInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SeenSlotInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SeenJumpInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasSeenInventoryPickup = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasSeenInventoryDrop = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasSeenSprintInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasSeenLightInfo = false;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float Oxygen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float Sustenance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float Exhaustion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FInventoryItem> InventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FSlotData Paperdoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTutorialState TutorialState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform PlayerTransform;
};

USTRUCT(BlueprintType)
struct FAirlockSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid AirlockID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAirlockState AirlockState;
};

USTRUCT(BlueprintType)
struct FLevelItemSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform ItemTransform;
};

USTRUCT(BlueprintType)
struct FContainerSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ContainerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> InventoryItems;
};

USTRUCT(BlueprintType)
struct FTimeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Day = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hour = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondsLeftInHour = 0.0f;
};

USTRUCT(BlueprintType)
struct FWorldData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAirlockSaveData> AirlockData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLevelItemSaveData> LevelItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FContainerSaveData> ContainerData;
};


UCLASS()
class PROXIMADIVIDE_API USurvivalScifi_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SlotNumber = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentLevelName = TEXT("L_Ship");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlayerStartTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnviroment Enviroment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FWorldData> MapData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FObjectivesData ObjectivesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimeData TimeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsExitSave = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWorldData ExitMapData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData ExitPlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FObjectivesData ExitObjectivesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimeData ExitTimeData;


	UFUNCTION()
	void AdvanceHours(int HoursToAdvance);
};
