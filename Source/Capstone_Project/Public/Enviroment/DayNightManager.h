// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightManager.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API ADayNightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FColor DaytimeColor;

	UPROPERTY(EditDefaultsOnly)
	FColor NighttimeColor;

	UPROPERTY(EditDefaultsOnly)
	FColor DaytimeFogColor;

	UPROPERTY(EditDefaultsOnly)
	FColor NighttimeFogColor;

	UPROPERTY(VisibleAnywhere)
	class ASurvivalScifiGameMode* GameMode;

	UPROPERTY(VisibleAnywhere)
	class AActor* Sun;

	UPROPERTY(VisibleAnywhere)
	class AActor* GoodSky;

	UPROPERTY(VisibleAnywhere)
	class AActor* SkySphere;

	UPROPERTY(VisibleAnywhere)
	class UDirectionalLightComponent* SunLight;

	UPROPERTY(VisibleAnywhere)
	class AExponentialHeightFog* ExponentialHeightFog;

	UPROPERTY(VisibleAnywhere)
	class ASkyLight* SkyLight;

	UPROPERTY()
	TArray<class ALightActor*> LightActors;

	UFUNCTION()
	void OnHourTick();

	UFUNCTION()
	bool IsDayTime();

	UFUNCTION()
	void ToggleLights();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
