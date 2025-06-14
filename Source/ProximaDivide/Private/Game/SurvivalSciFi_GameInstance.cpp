// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalSciFi_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "AkGameplayStatics.h"
#include "Character/Player/PlayerCharacter.h"
#include "Game/SurvivalScifiGameMode.h"
#include "Game/MissionStructs.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "EngineUtils.h"
#include "Enviroment/Door/Airlock.h"
#include "Item/SurvivalScifi_Item.h"
#include "Enviroment/Container.h"

void USurvivalSciFi_GameInstance::UpdateMapName()
{
	if (CurrentSaveGame != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateMapName called. OldName = %s, NewName = %s"), *CurrentSaveGame->CurrentLevelName.ToString(), *GetCurrentMapName().ToString());

		CurrentSaveGame->CurrentLevelName = GetCurrentMapName();
	}
}

FName USurvivalSciFi_GameInstance::GetCurrentMapName() const
{
	UWorld* World = GetWorld();
	if (!World) return NAME_None;
	FString MapName = World->GetMapName();
	FString CleanMapName = MapName;
	CleanMapName.RemoveFromStart(World->StreamingLevelsPrefix);
	return FName(*CleanMapName);
}

FWorldData USurvivalSciFi_GameInstance::GetCurrentMapData()
{
	static FWorldData DummyData; // fallback if not found
	if (CurrentSaveGame == nullptr) return DummyData;

	if (CurrentSaveGame->bIsExitSave)
	{
		return CurrentSaveGame->ExitMapData;
	}

	else
	{
		FName MapName = GetCurrentMapName();
		if (FWorldData* Found = CurrentSaveGame->MapData.Find(MapName))
		{
			return *Found;
		}
		return DummyData;
	}
}

FMapStartData USurvivalSciFi_GameInstance::GetCurrentMapStartData() const
{
	if (CurrentSaveGame != nullptr)
	{
		return CurrentSaveGame->MapStartData();
	}

	return FMapStartData();
}

bool USurvivalSciFi_GameInstance::HasMapDataForCurrentMap() const
{
	if (CurrentSaveGame == nullptr) return false;
	if (CurrentSaveGame->MapData.Contains(GetCurrentMapName()))
	{
		UE_LOG(LogTemp, Log, TEXT("Map data found for %s"), *GetCurrentMapName().ToString());
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No map data for %s"), *GetCurrentMapName().ToString());
		return false;
	}
	
}

void USurvivalSciFi_GameInstance::LoadCurrentSaveMap()
{
	if (bLevelSwitchInProgress)
	{
		UE_LOG(LogTemp, Log, TEXT("Tring opening level during level switch"));
		return;
	}

	bLevelSwitchInProgress = true;

	FString LevelNameString = CurrentSaveGame->CurrentLevelName.ToString();
	UE_LOG(LogTemp, Log, TEXT("Opening level: %s"), *LevelNameString);
	UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
}

USurvivalScifi_SaveGame* USurvivalSciFi_GameInstance::GetCurrentSaveGame()
{
	if (CurrentSaveGame == nullptr)
	{
		if (DoesSlotExist(0))
		{
			LoadSlot(0);
			UpdateMapName();
		}
		else
		{
			CurrentSaveGame = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::CreateSaveGameObject(USurvivalScifi_SaveGame::StaticClass()));

			if (CurrentSaveGame != nullptr)
			{
				CurrentSaveGame->SlotNumber = 0;
				UpdateMapName();
				SaveCurrentGame();
			}
		}
	}

	return CurrentSaveGame;
}

void USurvivalSciFi_GameInstance::SaveCurrentGame(int AdvanceHours, bool bIsExitSave)
{
	if (CurrentSaveGame != nullptr)
	{
		CurrentSaveGame->bIsExitSave = bIsExitSave;

		ASurvivalScifiGameMode* GameMode = Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode != nullptr)
		{
			if (bIsExitSave)
			{
				CurrentSaveGame->ExitMapData = GameMode->GetSaveData();
				CurrentSaveGame->ExitTimeData = GameMode->GetTimeData();
			}
			else
			{
				CurrentSaveGame->MapData.FindOrAdd(GetCurrentMapName()) = GameMode->GetSaveData();
				CurrentSaveGame->TimeData = GameMode->GetTimeData();
			}
			UE_LOG(LogTemp, Log, TEXT("Saved World Data"));
		}

		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player != nullptr)
		{
			if (bIsExitSave)
			{
				CurrentSaveGame->ExitPlayerData = Player->GetSaveData();
				CurrentSaveGame->ExitObjectivesData = Player->GetObjectiveSaveData();
			}
			else
			{
				CurrentSaveGame->PlayerData = Player->GetSaveData();
				CurrentSaveGame->ObjectivesData = Player->GetObjectiveSaveData();
			}
			UE_LOG(LogTemp, Log, TEXT("Saved Player Data"));
		}

		CurrentSaveGame->AdvanceHours(AdvanceHours);
		
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
		NewSave->PlayerData = InitialPlayerData;
		NewSave->TimeData = InitialTimeData;
		NewSave->Enviroment = InitialEnviroment;
		NewSave->CurrentLevelName = InitialLevelName;
		NewSave->PlayerStartTag = InitialPlayerStartTag;
		NewSave->MapData.Empty(); // Clear any existing map data

		CurrentSaveGame = NewSave;

		FString SlotName = "Slot" + FString::FromInt(SlotNumber);
		UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);

		UGameplayStatics::OpenLevel(this, CurrentSaveGame->CurrentLevelName);
	}
}

void USurvivalSciFi_GameInstance::StartSkipIntroGame(int SlotNumber)
{
	UE_LOG(LogTemp, Log, TEXT("Starting new game on slot %d"), SlotNumber);

	USurvivalScifi_SaveGame* NewSave = Cast<USurvivalScifi_SaveGame>(UGameplayStatics::CreateSaveGameObject(USurvivalScifi_SaveGame::StaticClass()));
	if (NewSave)
	{
		NewSave->SlotNumber = SlotNumber;
		NewSave->PlayerData = SkipIntroPlayerData;
		NewSave->TimeData = SkipIntroTimeData;
		NewSave->Enviroment = SkipIntroEnviroment;
		NewSave->CurrentLevelName = SkipIntroLevelName;
		NewSave->PlayerStartTag = SkipIntroPlayerStartTag;
		NewSave->MapData.Empty(); // Clear any existing map data

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
	LoadCurrentSaveMap();
}

void USurvivalSciFi_GameInstance::SwitchToMap(FName MapName, FName StartTag)
{
	if (GetCurrentMapName() == MapName)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already on map %s — skipping switch."), *MapName.ToString());
		return;
	}

	if (bLevelSwitchInProgress) return;

	UE_LOG(LogTemp, Warning, TEXT("SwitchToMap called"));

	if (CurrentSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SwitchToMap called but CurrentSaveGame is null!"));
		return;
	}

	// Apply new Map Name and Start Tag
	if (StartTag != "") CurrentSaveGame->PlayerStartTag = StartTag;
	CurrentSaveGame->CurrentLevelName = MapName;
	SaveCurrentGame();

	if (CurrentSaveGame->CurrentLevelName == "L_Planet" && CurrentSaveGame->TimeData.Day == 0 && GetCurrentMapName() != "L_Ship")
	{
		if (CurrentSaveGame->MapData.Contains("L_Planet"))
		{
			UE_LOG(LogTemp, Error, TEXT("SwitchToMap called from ship, save already has planet data"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SwitchToMap called from ship, save does not have planet data"));
		}
		
	}

	LoadCurrentSaveMap();
	UE_LOG(LogTemp, Warning, TEXT("SwitchToMap call end"));
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
	UE_LOG(LogTemp, Log, TEXT("Setting enviroment to %s"), *UEnum::GetValueAsString(Enviroment));

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

	case EEnviroment::PostCrash:
		UAkGameplayStatics::SetState(PostCrashState);
		if (CurrentSaveGame != nullptr) CurrentSaveGame->Enviroment = EEnviroment::PostCrash;
		break;
	}

	if (GetWorld()->WorldType == EWorldType::PIE && !bMusicAndAmbience) PlayMusicAndAmbience();
}

void USurvivalSciFi_GameInstance::StartWakeFromSleep(int HoursToSleep, FName PlayerStartTag)
{
	if (HoursToSleep < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("StartWakeFromSleep called with negative hours: %d"), HoursToSleep);
		return;			
	}

	if (CurrentSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StartWakeFromSleep called but CurrentSaveGame is null!"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Going to sleep for %d hours"), HoursToSleep);

	CurrentSaveGame->PlayerStartTag = PlayerStartTag;
	SaveCurrentGame(HoursToSleep);
	LoadCurrentSaveMap();
}

void USurvivalSciFi_GameInstance::StartRespawn()
{
	UE_LOG(LogTemp, Warning, TEXT("StartRespawn called"));
	SetEnviroment(EEnviroment::Inside);
	CurrentSaveGame->bIsExitSave = false; // Reset exit save flag
	LoadCurrentSaveMap();
}

// Streams in a level and restores save data after load
void USurvivalSciFi_GameInstance::StreamInLevelAndRestore(FName LevelName)
{
	UWorld* World = GetWorld();
	if (!World) return;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnLevelStreamedIn");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = __LINE__; // Unique ID

	// Stream in the level (async, not blocking)
	UGameplayStatics::LoadStreamLevel(World, LevelName, true, false, LatentInfo);
}

// Called when the streamed level is fully loaded and visible
void USurvivalSciFi_GameInstance::OnLevelStreamedIn()
{
	//RestoreLevelObjects();
}

// Restores all objects (airlocks, items, containers, etc.) from save data for the current map
void USurvivalSciFi_GameInstance::RestoreLevelObjects()
{
	if (!CurrentSaveGame) return;

	FWorldData Data = GetCurrentMapData();
	//PopulateLevelFromData(GetCurrentMapData());
	
}

void USurvivalSciFi_GameInstance::SaveAndExitGame()
{
	UE_LOG(LogTemp, Log, TEXT("Exiting Game..."));
	SaveCurrentGame(0, true);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_Start"));
}



