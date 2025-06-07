// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Enviroment/EEnviroment.h"
#include "SurvivalScifi_SaveGame.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API USurvivalScifi_SaveGame : public USaveGame
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
	bool bHasCompletedShipIntro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnviroment Enviroment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Day = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hour = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondsLeftInHour;
	
};
