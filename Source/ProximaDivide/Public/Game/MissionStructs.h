#pragma once

#include "CoreMinimal.h"
#include "Game/MissionDataAsset.h"
#include "MissionStructs.generated.h"

USTRUCT(BlueprintType)
struct FMissionProgress
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UMissionDataAsset* Mission = nullptr;

	UPROPERTY(EditAnywhere)
	int CurrentObjectiveIndex = 0;

	UPROPERTY(EditAnywhere)
	TArray<int> CompletedObjectives;

	bool operator==(const FMissionProgress& Other) const
	{
		return Mission == Other.Mission;
	}
};

USTRUCT(BlueprintType)
struct FObjectivesData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMissionDataAsset*> IncompleteMissions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMissionProgress> MissionProgresses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMissionDataAsset*> CompleteMissions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentMission = -1;
};