// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerObjectivesComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "Game/MissionStructs.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/ObjectiveMarkerInterface.h"

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
	UE_LOG(LogTemp, Log, TEXT("Completing current objective"));

	TurnOffObjectiveMarker(GetCurrentObjective().ActorTag);

	UMissionDataAsset* CurrentMissionPtr = GetCurrentMission();
	int32 Index = MissionProgresses.IndexOfByPredicate([CurrentMissionPtr](const FMissionProgress& Progress)
	{
		return Progress.Mission == CurrentMissionPtr;
	});

	if (Index != INDEX_NONE && CurrentMissionPtr)
	{
		FMissionProgress& Progress = MissionProgresses[Index];
		Progress.CompletedObjectives.Add(Progress.CurrentObjectiveIndex);
		Progress.CurrentObjectiveIndex++;

		// Check if all objectives are completed
		if (CurrentMissionPtr->Objectives.IsValidIndex(Progress.CurrentObjectiveIndex) == false)
		{
			// Remove from incomplete, add to complete
			if (IncompleteMissions.IsValidIndex(CurrentMission))
			{
				IncompleteMissions.RemoveAt(CurrentMission);
			}
			CompleteMissions.Add(CurrentMissionPtr);
			CurrentMission = -1;
		}
		else
		{
			TurnOnObjectiveMarker(CurrentMissionPtr->Objectives[Progress.CurrentObjectiveIndex].ActorTag);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Current mission progress not found!"));
	}

	// Update HUD
	if (APlayerCharacter* Player = GetOwner<APlayerCharacter>())
	{
		if (ASurvivalScifi_HUD* HUD = Player->GetHUD())
		{
			HUD->UpdateObjectives();
		}
	}
}

void UPlayerObjectivesComponent::TurnOnObjectiveMarker(FName ActorTag)
{
    UWorld* World = GetWorld();
    if (!World) return;

    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllActors);

    for (AActor* Actor : AllActors)
    {
        if (Actor && Actor->Tags.Num() > 0 && Actor->Tags[0].ToString() == ActorTag.ToString())
        {
            if (IObjectiveMarkerInterface* Marker = Cast<IObjectiveMarkerInterface>(Actor))
            {
                Marker->ShowObjectiveMarker();
            }
            break; // Only one actor will match
        }
    }
}

void UPlayerObjectivesComponent::TurnOffObjectiveMarker(FName ActorTag)
{
    UWorld* World = GetWorld();
    if (!World) return;

    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllActors);

    for (AActor* Actor : AllActors)
    {
        if (Actor && Actor->Tags.Num() > 0 && Actor->Tags[0].ToString() == ActorTag.ToString())
        {
            if (IObjectiveMarkerInterface* Marker = Cast<IObjectiveMarkerInterface>(Actor))
            {
                Marker->HideObjectiveMarker();
            }
            break; // Only one actor will match
        }
    }
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

	TurnOnObjectiveMarker(MissionDataAsset->Objectives[0].ActorTag);
}

void UPlayerObjectivesComponent::OnInteractWithActor(FName actorTag)
{
	UE_LOG(LogTemp, Log, 
		TEXT("Checking %s objective, actor tag = %s, objective tag =%s"), 
		GetCurrentObjective().ObjectiveType == EObjectiveType::Interaction ? TEXT("interaction") : TEXT("non interaction"),
		* actorTag.ToString(),
		*GetCurrentObjective().ActorTag.ToString());

	if (IncompleteMissions.Num() > 0 && GetCurrentObjective().ObjectiveType == EObjectiveType::Interaction && GetCurrentObjective().ActorTag == actorTag)
	{
		CompleteCurrentObjective();
	}
}

void UPlayerObjectivesComponent::OnArriveAtObjective(FName actorTag)
{
	UE_LOG(LogTemp, Log,
		TEXT("Checking %s objective, actor tag = %s, objective tag =%s"),
		GetCurrentObjective().ObjectiveType == EObjectiveType::GoTo ? TEXT("GoTo") : TEXT("non GotTo"),
		*actorTag.ToString(),
		*GetCurrentObjective().ActorTag.ToString());

	if (IncompleteMissions.Num() > 0 && GetCurrentObjective().ObjectiveType == EObjectiveType::GoTo && GetCurrentObjective().ActorTag == actorTag)
	{
		CompleteCurrentObjective();
	}
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

