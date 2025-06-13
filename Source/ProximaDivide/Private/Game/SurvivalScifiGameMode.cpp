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
	GameInstance->bLevelSwitchInProgress = false;
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

	UE_LOG(LogTemp, Log, TEXT("Set Day = %d, Hour = %d, RemaingSeconds = %f"), Day, Hour, SecondsLeftInHour);

	if (bRestoreObjectsOnBeginPlay && !GameInstance->HasMapDataForCurrentMap())
	{
		UE_LOG(LogTemp, Log, TEXT("LoadDataFromSave restoring level objects"));
		PopulateLevelFromData(GameInstance->GetCurrentMapData());
		bWorldObjectsRestored = true;
	}
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

void ASurvivalScifiGameMode::PopulateLevelFromData(FWorldData Data)
{
    // Restore Airlocks
    if (Data.AirlockData.Num() > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Populating level: Iterating airlocks"));
        TMap<FGuid, AAirlock*> AirlockMap;
        for (TActorIterator<AAirlock> It(GetWorld()); It; ++It)
        {
            AAirlock* Airlock = *It;
            if (!Airlock)
            {
                UE_LOG(LogTemp, Warning, TEXT("Null Airlock found in world!"));
                continue;
            }
            AirlockMap.Add(Airlock->GetAirlockID(), Airlock);
        }

        UE_LOG(LogTemp, Log, TEXT("Populating level: Restoring airlock states"));
        for (const FAirlockSaveData& Save : Data.AirlockData)
        {
            AAirlock** Found = AirlockMap.Find(Save.AirlockID);
            if (!Found || !*Found)
            {
                UE_LOG(LogTemp, Warning, TEXT("Airlock with ID %s not found!"), *Save.AirlockID.ToString());
                continue;
            }
            if ((*Found)->IsPendingKillPending() || !IsValid(*Found))
            {
                UE_LOG(LogTemp, Warning, TEXT("Airlock with ID %s is invalid or pending kill!"), *Save.AirlockID.ToString());
                continue;
            }
            (*Found)->SetAirlockState(Save.AirlockState);
        }
    }

    // Restore Items
    if (Data.LevelItems.Num() > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Populating level: Destroying existing items"));
        for (TActorIterator<ASurvivalScifi_Item> It(GetWorld()); It; ++It)
        {
            if (*It)
            {
                It->Destroy();
            }
        }

        UE_LOG(LogTemp, Log, TEXT("Populating level: Spawning saved items"));
        for (const FLevelItemSaveData& ItemData : Data.LevelItems)
        {
            if (!ItemData.ItemClass)
            {
                UE_LOG(LogTemp, Warning, TEXT("ItemData.ItemClass is null! Skipping item."));
                continue;
            }
            FActorSpawnParameters SpawnParams;
            ASurvivalScifi_Item* NewItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(
                ItemData.ItemClass, ItemData.ItemTransform, SpawnParams);
            if (!NewItem)
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn item of class %s"), *ItemData.ItemClass->GetName());
                continue;
            }
            NewItem->GetItemID() = ItemData.ItemID;
        }
    }

    // Restore Containers
    if (Data.ContainerData.Num() > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Populating level: Iterating containers"));
        TMap<FGuid, AContainer*> ContainerMap;
        for (TActorIterator<AContainer> It(GetWorld()); It; ++It)
        {
            AContainer* Container = *It;
            if (!Container)
            {
                UE_LOG(LogTemp, Warning, TEXT("Null Container found in world!"));
                continue;
            }
            ContainerMap.Add(Container->GetContainerID(), Container);
        }

        UE_LOG(LogTemp, Log, TEXT("Populating level: Loading container states"));
        for (const FContainerSaveData& Save : Data.ContainerData)
        {
            AContainer** Found = ContainerMap.Find(Save.ContainerID);
            if (!Found || !*Found)
            {
                UE_LOG(LogTemp, Warning, TEXT("Container with ID %s not found!"), *Save.ContainerID.ToString());
                continue;
            }
            if ((*Found)->IsPendingKillPending() || !IsValid(*Found))
            {
                UE_LOG(LogTemp, Warning, TEXT("Container with ID %s is invalid or pending kill!"), *Save.ContainerID.ToString());
                continue;
            }
            (*Found)->LoadContainerSaveData(Save);
        }
    }
}

void ASurvivalScifiGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    if (bRestoreObjectsOnStartingNewPlayer && !bRestoreObjectsOnBeginPlay && !bWorldObjectsRestored)
    {
		UE_LOG(LogTemp, Log, TEXT("HandleStartingNewPlayer restoring level objects"));

		USurvivalSciFi_GameInstance* GI = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
		if (GI != nullptr && GI->HasMapDataForCurrentMap())
        {
            PopulateLevelFromData(GI->GetCurrentMapData());
        }
        bWorldObjectsRestored = true;
    }

    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}
