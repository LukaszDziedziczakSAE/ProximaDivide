// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerObjectivesComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "Game/MissionStructs.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"

// Sets default values for this component's properties
UPlayerObjectivesComponent::UPlayerObjectivesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerObjectivesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UPlayerObjectivesComponent::CompleteCurrentObjective()
{
	FMissionProgress Progress = GetCurrentMissionProgress();
	Progress.CompletedObjectives.Add(Progress.CurrentObjectiveIndex);
	Progress.CurrentObjectiveIndex++;

	UMissionDataAsset* Mission = GetCurrentMission();
	if (Progress.CurrentObjectiveIndex >= Mission->Objectives.Num())
	{
		IncompleteMissions.RemoveAt(CurrentMission);
		CompleteMissions.Add(Mission);
		CurrentMission = -1;
	}

	GetOwner<APlayerCharacter>()->GetHUD()->UpdateObjectives();
}

// Called every frame
void UPlayerObjectivesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

FMissionProgress UPlayerObjectivesComponent::GetCurrentMissionProgress()
{

	//return MissionProgresses[MissionProgresses.IndexOfByKey(GetCurrentMission())];

	UMissionDataAsset* CurrentMissionPtr = GetCurrentMission();
	int32 Index = MissionProgresses.IndexOfByPredicate([CurrentMissionPtr](const FMissionProgress& Progress)
		{
			return Progress.Mission == CurrentMissionPtr;
		});

	if (Index != INDEX_NONE)
	{
		return MissionProgresses[Index];
	}

	// Return default or handle error if mission progress not found
	return FMissionProgress();
}

FObjectiveData UPlayerObjectivesComponent::GetCurrentObjective()
{
	return GetCurrentMission()->Objectives[GetCurrentMissionProgress().CurrentObjectiveIndex];
}

void UPlayerObjectivesComponent::AddNewMission(UMissionDataAsset* MissionDataAsset)
{
	if (MissionDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerObjectivesComponent::AddNewMission received null MissionDataAsset"));
		return;
	}

	if (IncompleteMissions.Contains(MissionDataAsset) || CompleteMissions.Contains(MissionDataAsset)) return;

	IncompleteMissions.Add(MissionDataAsset);
	FMissionProgress MissionProgress = FMissionProgress();
	MissionProgress.Mission = MissionDataAsset;
	MissionProgresses.Add(MissionProgress);
	CurrentMission = IncompleteMissions.IndexOfByKey(MissionDataAsset);
	
	GetOwner<APlayerCharacter>()->GetHUD()->UpdateObjectives();
	UE_LOG(LogTemp, Log, TEXT("Added new mission"));
}

void UPlayerObjectivesComponent::OnInteractWithActor(FName actorTag)
{
	UE_LOG(LogTemp, Log, TEXT("Checking %s objective, actor tag = %s, objective tag =%s"), GetCurrentObjective().ObjectiveType != EObjectiveType::Interaction ? TEXT("interaction") : TEXT("non interaction"), * actorTag.ToString(), *GetCurrentObjective().InteractionActorTag.ToString());
	if (IncompleteMissions.Num() == 0 
		|| GetCurrentObjective().ObjectiveType != EObjectiveType::Interaction 
		|| GetCurrentObjective().InteractionActorTag != actorTag) 
		return;

	CompleteCurrentObjective();
}

FObjectivesData UPlayerObjectivesComponent::GetSaveData()
{
	FObjectivesData Data = FObjectivesData();

	Data.IncompleteMissions = IncompleteMissions;
	Data.CompleteMissions = CompleteMissions;
	Data.MissionProgresses = MissionProgresses;
	Data.CurrentMission = CurrentMission;

	return Data;
}

void UPlayerObjectivesComponent::LoadDataFromSave(FObjectivesData SaveData)
{
	IncompleteMissions = SaveData.IncompleteMissions;
	CompleteMissions = SaveData.CompleteMissions;
	MissionProgresses = SaveData.MissionProgresses;
	CurrentMission = SaveData.CurrentMission;
	GetOwner<APlayerCharacter>()->GetHUD()->UpdateObjectives();
}

