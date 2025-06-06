// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SurvivalScifiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DirectionalLightComponent.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Game/SurvivalSciFi_GameInstance.h"
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

	TArray<AActor*> SunActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Sun"), SunActors);
	if (SunActors.Num() > 0) Sun = SunActors[0];

	if (Sun != nullptr) SunLight = Sun->GetComponentByClass<UDirectionalLightComponent>();

	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
	if (GameInstance != nullptr)
	{
		GameInstance->OnLevelStart();
	}
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

		if (SunLight != nullptr)
		{
			if (Hour >= 6 && Hour < 20)
			{
				SunLight->SetIntensity(8.0f);
			}
			else
			{
				SunLight->SetIntensity(0.0f);
			}
		}
	}

	if (Sun != nullptr)
	{
		float angle = FMath::Lerp(185.0f, 355.0f, GetTimeProgress());
		Sun->SetActorRotation(FQuat::MakeFromEuler(FVector(0, angle, 0)));
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

		if (GameInstance != nullptr && GameInstance->GetCurrentSaveGame() != nullptr && PlayerStarts.Num() > 0)
		{
			for (APlayerStart* PlayerStart : PlayerStarts)
			{
				if (PlayerStart->PlayerStartTag == GameInstance->GetCurrentSaveGame()->PlayerStartTag)
					return PlayerStart;
			}
		}
	}

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

void ASurvivalScifiGameMode::LoadGame(int SlotNumber)
{
	if (GameInstance == nullptr) return;
	GameInstance->StartLoadGame(SlotNumber);
}


