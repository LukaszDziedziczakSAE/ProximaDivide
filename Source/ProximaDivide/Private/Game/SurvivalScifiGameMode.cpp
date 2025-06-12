// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SurvivalScifiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "Enviroment/Door/Airlock.h"
#include "EngineUtils.h"
#include "Item/SurvivalScifi_Item.h"
#include "Enviroment/Container.h"

ASurvivalScifiGameMode::ASurvivalScifiGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ASurvivalScifiGameMode::BeginPlay()
{
	Super::BeginPlay();

	SecondsLeftInHour = SecondsPerHour;

	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;
	GameInstance->OnLevelStart();
	LoadDataFromSave();
}

void ASurvivalScifiGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SecondsLeftInHour -= DeltaSeconds;

	if (SecondsLeftInHour <= 0)
	{
		SecondsLeftInHour = SecondsPerHour;
		Hour++;

		if (Hour >= 24)
		{
			Hour = 0;
			Day++;
		}

		OnHourTick.Broadcast();
	}
}

AActor* ASurvivalScifiGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	if (PlayerStartActors.Num() > 0)
	{
		TArray<APlayerStart*> PlayerStarts;
		for (AActor* Actor : PlayerStartActors)
		{
			if (APlayerStart* Start = Cast<APlayerStart>(Actor))
			{
				PlayerStarts.Add(Start);
			}
		}

		
		if (GameInstance == nullptr) 
			GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());

		if (GameInstance != nullptr && GameInstance->GetCurrentSaveGame() != nullptr && PlayerStarts.Num() > 0)
		{
			for (APlayerStart* PlayerStart : PlayerStarts)
			{
				if (PlayerStart->PlayerStartTag == GameInstance->GetCurrentSaveGame()->PlayerStartTag)
				{
					UE_LOG(LogTemp, Log, TEXT("ChoosePlayerStart returning %s"), *PlayerStart->PlayerStartTag.ToString());
					return PlayerStart;
				}
			}

			UE_LOG(LogTemp, Error, TEXT("ChoosePlayerStart did not find PlayerStartTag matching tag found in save (%s)"), *GameInstance->GetCurrentSaveGame()->PlayerStartTag.ToString());
		}

		else if (GameInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ChoosePlayerStart did not find GameInstance"));
		}
			
		else if (GameInstance->GetCurrentSaveGame() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ChoosePlayerStart did not find CurrentSaveGame"));
		}

		else if (PlayerStarts.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("ChoosePlayerStart No PlayerStarts found"));
		}
	}
	else UE_LOG(LogTemp, Error, TEXT("ChoosePlayerStart No PlayerStartActors found"));

	return Super::ChoosePlayerStart_Implementation(Player);
}

float ASurvivalScifiGameMode::GetTimeProgress()
{
	if (Hour >= 6 && Hour < 20)
	{
		int hour = Hour - 6;

		float progress = (float)hour / 14.0f;
		progress += ((SecondsPerHour - SecondsLeftInHour) / SecondsPerHour) * (1.0f / 14.0f);

		return progress;
	}
	else
	{
		return 0.0f;
	}
}

void ASurvivalScifiGameMode::UpdatePlayerStartTag(FName PlayerStartTag)
{
	if (GameInstance == nullptr) return;

	GameInstance->GetCurrentSaveGame()->PlayerStartTag = PlayerStartTag;
}

void ASurvivalScifiGameMode::SaveGame()
{
	if (GameInstance == nullptr) return;

	GameInstance->SaveCurrentGame();
}

struct FWorldData ASurvivalScifiGameMode::GetSaveData()
{
	FWorldData Data = FWorldData();

	// save airlock data
	Data.AirlockData.Empty();
	for (TActorIterator<AAirlock> It(GetWorld()); It; ++It)
	{
		AAirlock* Airlock = *It;
		FAirlockSaveData Save;
		Save.AirlockID = Airlock->GetAirlockID();
		Save.AirlockState = Airlock->GetAirlockState();
		Data.AirlockData.Add(Save);
	}

	// Save item data
	Data.LevelItems.Empty();
	for (TActorIterator<ASurvivalScifi_Item> It(GetWorld()); It; ++It)
	{
		ASurvivalScifi_Item* Item = *It;
		FLevelItemSaveData ItemData;
		ItemData.ItemID = Item->GetItemID(); // Use the getter here
		ItemData.ItemClass = Item->GetClass();
		ItemData.ItemTransform = Item->GetActorTransform();
		Data.LevelItems.Add(ItemData);
	}

	// Save container data
	Data.ContainerData.Empty();
	for (TActorIterator<AContainer> It(GetWorld()); It; ++It)
	{
		AContainer* Container = *It;
		Data.ContainerData.Add(Container->GetContainerSaveData());
	}

	return Data;
}

FTimeData ASurvivalScifiGameMode::GetTimeData()
{
	FTimeData TimeData = FTimeData();

	TimeData.Day = Day;
	TimeData.Hour = Hour;
	TimeData.SecondsLeftInHour = SecondsLeftInHour;

	return TimeData;
}

void ASurvivalScifiGameMode::LoadDataFromSave()
{
    if (GameInstance == nullptr || GameInstance->GetCurrentSaveGame() == nullptr)
        return;

	FTimeData TimeData = GameInstance->GetCurrentSaveGame()->TimeData;

    Day = TimeData.Day;
    Hour = TimeData.Hour;
    SecondsLeftInHour = TimeData.SecondsLeftInHour;
    OnHourTick.Broadcast();

	if (!GameInstance->HasMapDataForCurrentMap()) return;

    FWorldData Data = GameInstance->GetCurrentMapData();

    // Load airlock data
    TMap<FName, AAirlock*> AirlockMap;
    for (TActorIterator<AAirlock> It(GetWorld()); It; ++It)
    {
        AAirlock* Airlock = *It;
        AirlockMap.Add(Airlock->GetAirlockID(), Airlock);
    }
    for (const FAirlockSaveData& Save : Data.AirlockData)
    {
        if (AAirlock** Found = AirlockMap.Find(Save.AirlockID))
        {
            (*Found)->SetAirlockState(Save.AirlockState);
        }
    }

    // Only delete and respawn items if there is saved item data
    if (Data.LevelItems.Num() > 0)
    {
        // Remove existing items before respawning
        for (TActorIterator<ASurvivalScifi_Item> It(GetWorld()); It; ++It)
        {
            It->Destroy();
        }

        // Spawn items from save data
        for (const FLevelItemSaveData& ItemData : Data.LevelItems)
        {
            FActorSpawnParameters SpawnParams;
            ASurvivalScifi_Item* NewItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(
                ItemData.ItemClass, ItemData.ItemTransform, SpawnParams);
            if (NewItem)
            {
                NewItem->GetItemID() = ItemData.ItemID;
            }
        }
    }

    // Load container data
    if (Data.ContainerData.Num() > 0)
    {
        // Map existing containers by ID
        TMap<FGuid, AContainer*> ContainerMap;
        for (TActorIterator<AContainer> It(GetWorld()); It; ++It)
        {
            AContainer* Container = *It;
            ContainerMap.Add(Container->GetContainerID(), Container);
        }

        // Apply saved data to matching containers
        for (const FContainerSaveData& Save : Data.ContainerData)
        {
            if (AContainer** Found = ContainerMap.Find(Save.ContainerID))
            {
                (*Found)->LoadContainerSaveData(Save);
            }
        }
    }
}

void ASurvivalScifiGameMode::LoadGame(int SlotNumber)
{
	if (GameInstance == nullptr) return;
	GameInstance->StartLoadGame(SlotNumber);
}

FString ASurvivalScifiGameMode::GetCurrentMapName()
{
	FString MapName = GetWorld()->GetMapName();
	// Remove PIE prefix if it exists
	FString CleanMapName = MapName;
	CleanMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	return CleanMapName;
}

UMissionDataAsset* ASurvivalScifiGameMode::GetOnStartMission()
{
	if (OnStartGiveMission.Contains(GetCurrentMapName()))
	{
		return OnStartGiveMission[GetCurrentMapName()];
	}
	else return nullptr;
}


