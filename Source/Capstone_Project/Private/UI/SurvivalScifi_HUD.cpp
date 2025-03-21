// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/SurvivalScifi_HUD.h"
#include "UI/SurvivalScifiUserWidget.h"

void ASurvivalScifi_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerStatsClass != nullptr) PlayerStats = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), PlayerStatsClass);
	if (PlayerStats != nullptr) PlayerStats->AddToViewport();

	if (ActionBarClass != nullptr) ActionBar = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), ActionBarClass);
	if (ActionBar != nullptr) ActionBar->AddToViewport();
}

void ASurvivalScifi_HUD::ShowInventory()
{
	if (InventoryClass != nullptr) Inventory = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), InventoryClass);
	if (Inventory != nullptr) Inventory->AddToViewport();
}

void ASurvivalScifi_HUD::HideInventory()
{
	if (Inventory != nullptr) Inventory->RemoveFromViewport();
	Inventory = nullptr;
}
