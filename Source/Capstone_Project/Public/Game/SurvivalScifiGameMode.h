// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalScifiGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API ASurvivalScifiGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivalScifiGameMode();

protected:
	UPROPERTY(EditAnywhere)
	int Day = 1;

	UPROPERTY(EditAnywhere)
	int Hour = 9;

	UPROPERTY(EditAnywhere)
	float SecondsPerHour = 120;

	UPROPERTY(VisibleAnywhere)
	float SecondsLeftInHour;

	UPROPERTY()
	class AActor* Sun;

	UPROPERTY()
	class UDirectionalLightComponent* SunLight;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintPure)
	int GetDay() { return Day; }

	UFUNCTION(BlueprintPure)
	int GetHour() { return Hour; }

	UFUNCTION(BlueprintPure)
	float GetTimeProgress();
};
