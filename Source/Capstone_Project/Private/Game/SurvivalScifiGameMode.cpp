// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SurvivalScifiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DirectionalLightComponent.h"


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
	Sun = SunActors[0];

	
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

		UDirectionalLightComponent* SunLight = Sun->GetComponentByClass<UDirectionalLightComponent>();
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
