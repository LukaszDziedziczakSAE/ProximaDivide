// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Enviroment/EEnviroment.h"
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

	UFUNCTION()
	void AdvanceHours(int HoursToAdvance);
};
