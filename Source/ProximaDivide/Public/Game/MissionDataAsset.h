// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MissionDataAsset.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	NoObjectiveType UMETA(DisplayName = "None"),
	Tutorial        UMETA(DisplayName = "Tutorial"),
	Interaction     UMETA(DisplayName = "Interaction"),
	GoTo            UMETA(DisplayName = "Go To")
};

USTRUCT(BlueprintType)
struct FObjectiveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bOptional;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName InteractionActorTag;

	bool operator==(const FObjectiveData& Other) const
	{
		return Description.EqualTo(Other.Description);
	}
};

UCLASS()
class PROXIMADIVIDE_API UMissionDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MissionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FObjectiveData> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bMultiObjective; // if the mission is not linear
	
};
