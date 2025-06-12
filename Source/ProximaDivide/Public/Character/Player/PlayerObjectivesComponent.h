// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/MissionDataAsset.h"
#include "PlayerObjectivesComponent.generated.h"

//USTRUCT(BlueprintType)
//struct FMissionProgress
//{
//	GENERATED_BODY()
//
//public:
//
//	UPROPERTY(EditAnywhere)
//	class UMissionDataAsset* Mission = nullptr;
//
//	UPROPERTY(EditAnywhere)
//	int CurrentObjectiveIndex = 0;
//
//	UPROPERTY(EditAnywhere)
//	TArray<int> CompletedObjectives;
//
//	bool operator==(const FMissionProgress& Other) const
//	{
//		// Compare only the pointer to the mission if that's the unique identifier
//		return Mission == Other.Mission;
//	}
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UPlayerObjectivesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerObjectivesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TArray<UMissionDataAsset*> IncompleteMissions;

	UPROPERTY(VisibleAnywhere)
	TArray<struct FMissionProgress> MissionProgresses;

	UPROPERTY(VisibleAnywhere)
	TArray<UMissionDataAsset*> CompleteMissions;

	UPROPERTY(VisibleAnywhere)
	int CurrentMission = -1;

	UFUNCTION()
	void CompleteCurrentObjective();

	UFUNCTION()
	void TurnOnObjectiveMarker(FName ActorTag);

	UFUNCTION()
	void TurnOffObjectiveMarker(FName ActorTag);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	UMissionDataAsset* GetCurrentMission() const;

	UFUNCTION()
	FMissionProgress GetCurrentMissionProgress();

	FObjectiveData GetCurrentObjective();

	UFUNCTION()
	void AddNewMission(UMissionDataAsset* MissionDataAsset);

	UFUNCTION()
	void OnInteractWithActor(FName actorTag);

	UFUNCTION()
	void OnArriveAtObjective(FName actorTag);

	UFUNCTION(BlueprintPure)
	bool HasMissions() { return IncompleteMissions.Num() > 0; }

	UFUNCTION()
	struct FObjectivesData GetSaveData();

	UFUNCTION()
	void LoadDataFromSave(FObjectivesData SaveData);

};
