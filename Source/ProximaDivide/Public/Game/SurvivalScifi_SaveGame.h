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
};

USTRUCT(BlueprintType)
struct FAirlockSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AirlockID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAirlockState AirlockState;
};

USTRUCT(BlueprintType)
struct FWorldData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Day = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hour = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondsLeftInHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAirlockSaveData> AirlockData;
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
	FWorldData WorldData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FObjectivesData ObjectivesData;

	UFUNCTION()
	void AdvanceHours(int HoursToAdvance);
};
