// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalSciFi_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "AkGameplayStatics.h"
#include "Character/Player/PlayerCharacter.h"

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
		UE_LOG(LogTemp, Log, TEXT("Loading %s"), *SlotName);
		CurrentSaveGame = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (CurrentSaveGame == nullptr) return false;

		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player != nullptr)
		{
			Player->bIsInside = CurrentSaveGame->Enviroment != EEnviroment::Outside;
		}
		else UE_LOG(LogTemp, Error, TEXT("Did not find player character during %s load"), *SlotName);

		return true;
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
	bool Exists = UGameplayStatics::DoesSaveGameExist(SlotName, 0);
	UE_LOG(LogTemp, Log, TEXT("DoesSlotExist %s %s"), *SlotName, Exists ? TEXT("True") : TEXT("False"));
	return Exists;
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
		SetEnviroment(EEnviroment::Ship);
		UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
		UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
	}
}

void USurvivalSciFi_GameInstance::StartLoadGame(int SlotNumber)
{
	LoadSlot(SlotNumber);
	if (CurrentSaveGame == nullptr) return;

	//SetEnviroment(CurrentSaveGame->Enviroment);

	// Load Level
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

	// Apply new Map Name and Start Tag
	if (StartTag != "") CurrentSaveGame->PlayerStartTag = StartTag;
	CurrentSaveGame->CurrentLevelName = MapName;
	SaveSlot(CurrentSaveGame->SlotNumber);

	// Load Level
	FString LevelNameString = CurrentSaveGame->CurrentLevelName.ToString();
	UE_LOG(LogTemp, Log, TEXT("Switching to level: %s"), *LevelNameString);
	UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
}

void USurvivalSciFi_GameInstance::OnLevelStart()
{
	int DefaultSlot = 0;

	if (CurrentSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No save OnLevelStart"));
		if (DoesSlotExist(DefaultSlot))
		{
			LoadSlot(DefaultSlot);
			UpdateMapName();
			UE_LOG(LogTemp, Warning, TEXT("Loaded save OnLevelStart"));
		}
		else
		{
			CurrentSaveGame = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::CreateSaveGameObject(USurvivalScifi_SaveGame::StaticClass()));

			if (CurrentSaveGame != nullptr)
			{
				CurrentSaveGame->SlotNumber = DefaultSlot;
				UpdateMapName();
				SaveCurrentGame();
				UE_LOG(LogTemp, Warning, TEXT("Created new save OnLevelStart"));
			}
		}
	}
	if (CurrentSaveGame == nullptr) return;

	SetEnviroment(CurrentSaveGame->Enviroment);
}

void USurvivalSciFi_GameInstance::DeleteSlot(int SlotNumber)
{
	if (DoesSlotExist(SlotNumber))
	{
		FString SlotName = "Slot" + FString::FromInt(SlotNumber);
		UGameplayStatics::DeleteGameInSlot(SlotName,0);
	}
}

void USurvivalSciFi_GameInstance::PlayMusicAndAmbience()
{
	if (Ambience != nullptr)
	{
		UAkGameplayStatics::PostEvent(Ambience, nullptr, int32(0), FOnAkPostEventCallback(), false);
	}

	if (Music != nullptr)
	{
		UAkGameplayStatics::PostEvent(Music, nullptr, int32(0), FOnAkPostEventCallback(), false);
	}

	bMusicAndAmbience = true;
}

void USurvivalSciFi_GameInstance::SetEnviroment(EEnviroment Enviroment)
{
	switch (Enviroment)
	{
	case EEnviroment::Menu:
		UAkGameplayStatics::SetState(MenuState);
		//if (CurrentSaveGame != nullptr) CurrentSaveGame->Enviroment = EEnviroment::Menu;
		break;

	case EEnviroment::DecentCinematic:
		UAkGameplayStatics::SetState(DecentCinematicState);
		break;

	case EEnviroment::Inside:
		UAkGameplayStatics::SetState(InsideState);
		if (CurrentSaveGame != nullptr) CurrentSaveGame->Enviroment = EEnviroment::Inside;
		break;

	case EEnviroment::Outside:
		UAkGameplayStatics::SetState(OutsideState);
		if (CurrentSaveGame != nullptr) CurrentSaveGame->Enviroment = EEnviroment::Outside;
		break;

	case EEnviroment::Ship:
		UAkGameplayStatics::SetState(ShipState);
		if (CurrentSaveGame != nullptr) CurrentSaveGame->Enviroment = EEnviroment::Ship;
		break;
	}

	if (GetWorld()->WorldType == EWorldType::PIE && !bMusicAndAmbience) PlayMusicAndAmbience();
}

