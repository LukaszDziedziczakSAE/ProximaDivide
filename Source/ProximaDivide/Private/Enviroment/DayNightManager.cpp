// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/DayNightManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DirectionalLightComponent.h"
#include "Game/SurvivalScifiGameMode.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"
#include "Enviroment/LightActor.h"

// Sets default values
ADayNightManager::ADayNightManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayNightManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->OnHourTick.AddDynamic(this, &ADayNightManager::OnHourTick);
	}
	else UE_LOG(LogTemp, Error, TEXT("DayNightManager has no gameMode reference"))

	TArray<AActor*> FoundLights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALightActor::StaticClass(), FoundLights);
	for (AActor* Actor : FoundLights)
	{
		if (ALightActor* Light = Cast<ALightActor>(Actor))
		{
			LightActors.Add(Light);
		}
	}
	if (LightActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No LightActors found in the scene!"));
	}	

	// Find sun
	TArray<AActor*> SunActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Sun"), SunActors);
	if (SunActors.Num() > 0) Sun = SunActors[0];
	if (Sun != nullptr) SunLight = Sun->GetComponentByClass<UDirectionalLightComponent>();

	// Find GoodSky
	TArray<AActor*> SkyActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("GoodSky"), SkyActors);
	if (SkyActors.Num() > 0) GoodSky = SkyActors[0];

	// Find SkySphere
	TArray<AActor*> SphereActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SkySphere"), SphereActors);
	if (SphereActors.Num() > 0) SkySphere = SphereActors[0];

	// Find ExponentialHeightFog
	TArray<AActor*> FogActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExponentialHeightFog::StaticClass(), FogActors);
	if (FogActors.Num() > 0) ExponentialHeightFog = Cast<AExponentialHeightFog>(FogActors[0]);

	// Find SkyLight
	TArray<AActor*> SkyLightActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyLight::StaticClass(), SkyLightActors);
	if (SkyLightActors.Num() > 0) SkyLight = Cast<ASkyLight>(SkyLightActors[0]);


	OnHourTick();
}

void ADayNightManager::OnHourTick()
{
	//if (SunLight != nullptr) SunLight->SetIntensity(IsDayTime() ? 8.0f : 0.0f);
	if (Sun != nullptr) Sun->SetActorHiddenInGame(!IsDayTime());
	if (GoodSky != nullptr) GoodSky->SetActorHiddenInGame(IsDayTime());
	if (SkySphere != nullptr) SkySphere->SetActorHiddenInGame(!IsDayTime());
	if (ExponentialHeightFog != nullptr)
	{
		UExponentialHeightFogComponent* FogComponent = ExponentialHeightFog->GetComponent();
		if (FogComponent)
		{
			FogComponent->SetFogInscatteringColor(IsDayTime() ? DaytimeFogColor : NighttimeFogColor);
		}
	}
	if (SkyLight != nullptr && SkyLight->GetLightComponent())
	{
		SkyLight->GetLightComponent()->SetLightColor(IsDayTime() ? DaytimeColor : NighttimeColor);
		SkyLight->GetLightComponent()->MarkRenderStateDirty(); // Apply the change
	}

	ToggleLights();
}

bool ADayNightManager::IsDayTime()
{
	if (GameMode == nullptr) return false;
	return GameMode->GetHour() >= 6 && GameMode->GetHour() < 20;
}

void ADayNightManager::ToggleLights()
{
	for (ALightActor* Light : LightActors)
	{
		if (Light)
		{
			if (IsDayTime())
				Light->TurnOffLight();
			else
				Light->TurnOnLight();
		}
	}
}

// Called every frame
void ADayNightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode == nullptr) return;

	if (Sun != nullptr)
	{
		float angle = FMath::Lerp(185.0f, 355.0f, GameMode->GetTimeProgress());
		Sun->SetActorRotation(FQuat::MakeFromEuler(FVector(0, angle, 0)));
	}
}

