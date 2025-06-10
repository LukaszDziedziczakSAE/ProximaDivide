// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SurvivalScifiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Game/SurvivalScifi_SaveGame.h"

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

	Data.Day = Day;
	Data.Hour = Hour;
	Data.SecondsLeftInHour = SecondsLeftInHour;

	return Data;
}

void ASurvivalScifiGameMode::LoadDataFromSave()
{
	if (GameInstance->GetCurrentSaveGame() == nullptr) return;

	FWorldData Data = GameInstance->GetCurrentSaveGame()->WorldData;

	Day = Data.Day;
	Hour = Data.Hour;
	SecondsLeftInHour = Data.SecondsLeftInHour;
	OnHourTick.Broadcast();
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


