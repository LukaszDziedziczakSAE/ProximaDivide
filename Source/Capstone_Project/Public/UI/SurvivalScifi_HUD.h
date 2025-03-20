// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SurvivalScifi_HUD.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API ASurvivalScifi_HUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USurvivalScifiUserWidget> PlayerStatsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> ActionBarClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> InventoryClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* PlayerStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* ActionBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* Inventory;
};
