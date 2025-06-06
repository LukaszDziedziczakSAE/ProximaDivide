// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalSciFi_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SurvivalScifi_SaveGame.h"

void USurvivalSciFi_GameInstance::UpdateMapName()
{
	if (CurrentSaveGame != nullptr)
	{

		FString MapName = GetWorld()->GetMapName();
		// Remove PIE prefix if it exists
		FString CleanMapName = MapName;
		CleanMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		CurrentSaveGame->CurrentLevelName = FName(*CleanMapName);
	}
}

void USurvivalSciFi_GameInstance::SaveCurrentGame()
{
	if (CurrentSaveGame != nullptr)
	{
		SaveSlot(CurrentSaveGame->SlotNumber);
	}
}

bool USurvivalSciFi_GameInstance::LoadSlot(int SlotNumber)
{
	FString SlotName = "Slot" + FString::FromInt(SlotNumber);

	if (DoesSlotExist(SlotNumber))
	{
		CurrentSaveGame = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		return CurrentSaveGame != nullptr;
	}

	return false;
}

bool USurvivalSciFi_GameInstance::SaveSlot(int SlotNumber)
{
	if (CurrentSaveGame == nullptr) return false;

	FString SlotName = "Slot" + FString::FromInt(SlotNumber);
	UE_LOG(LogTemp, Log, TEXT("Saving %s"), *SlotName);
	return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
}

bool USurvivalSciFi_GameInstance::DoesSlotExist(int SlotNumber)
{
	FString SlotName = "Slot" + FString::FromInt(SlotNumber);
	UE_LOG(LogTemp, Log, TEXT("Loading %s"), *SlotName);
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void USurvivalSciFi_GameInstance::StartNewGame(int SlotNumber)
{
	UE_LOG(LogTemp, Log, TEXT("Starting new game on slot %d"), SlotNumber);
	USurvivalScifi_SaveGame* NewSave = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::CreateSaveGameObject(USurvivalScifi_SaveGame::StaticClass()));
	if (NewSave)
	{
		NewSave->SlotNumber = SlotNumber;
		CurrentSaveGame = NewSave;
		FString SlotName = "Slot" + FString::FromInt(SlotNumber);
		UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
		UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
	}
}

void USurvivalSciFi_GameInstance::StartLoadGame(int SlotNumber)
{
	LoadSlot(SlotNumber);

	if (CurrentSaveGame == nullptr) return;

	FString LevelNameString = CurrentSaveGame->CurrentLevelName.ToString();
	UE_LOG(LogTemp, Log, TEXT("Opening level: %s"), *LevelNameString);
	UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
}

void USurvivalSciFi_GameInstance::SwitchToMap(FName MapName, FName StartTag)
{
	if (CurrentSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SwitchToMap called but CurrentSaveGame is null!"));
		return;
	}

	if (StartTag != "") CurrentSaveGame->PlayerStartTag = StartTag;
	CurrentSaveGame->CurrentLevelName = MapName;
	SaveCurrentGame();
	FString LevelNameString = CurrentSaveGame->CurrentLevelName.ToString();
	UE_LOG(LogTemp, Log, TEXT("Switching to level: %s"), *LevelNameString);
	UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
}

void USurvivalSciFi_GameInstance::OnLevelStart()
{
	int DefaultSlot = 0;

	if (CurrentSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No save on Level Start"));
		if (DoesSlotExist(DefaultSlot))
		{
			LoadSlot(DefaultSlot);
			UpdateMapName();
			UE_LOG(LogTemp, Warning, TEXT("Loaded Save slot 0"));
		}
		else
		{
			CurrentSaveGame = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::CreateSaveGameObject(USurvivalScifi_SaveGame::StaticClass()));

			if (CurrentSaveGame != nullptr)
			{
				CurrentSaveGame->SlotNumber = DefaultSlot;
				UpdateMapName();
				SaveCurrentGame();
				UE_LOG(LogTemp, Warning, TEXT("Created new save"));
			}
		}
	}
}

void USurvivalSciFi_GameInstance::DeleteSlot(int SlotNumber)
{
	if (DoesSlotExist(SlotNumber))
	{
		FString SlotName = "Slot" + FString::FromInt(SlotNumber);
		UGameplayStatics::DeleteGameInSlot(SlotName,0);
	}
}

