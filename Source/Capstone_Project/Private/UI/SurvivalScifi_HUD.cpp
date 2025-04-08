// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/SurvivalScifi_HUD.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "UI/PlayerInventoryUserWidget.h"
#include "UI/CraftingMenuUserWidget.h"
#include "UI/InventoryItemUserWidget.h"
#include "Item/ItemDataAsset.h"
#include "UI/InventorySlotUserWidget.h"
#include "UI/NotificationsUserWidget.h"

void ASurvivalScifi_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerStatsClass != nullptr) PlayerStats = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), PlayerStatsClass);
	if (PlayerStats != nullptr) PlayerStats->AddToViewport();

	if (ActionBarClass != nullptr) ActionBar = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), ActionBarClass);
	if (ActionBar != nullptr) ActionBar->AddToViewport();

	if (CrosshairClass != nullptr) Crosshair = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), CrosshairClass);
	if (Crosshair != nullptr) Crosshair->AddToViewport();

	if (NotificationsClass != nullptr) Notifications = CreateWidget<UNotificationsUserWidget>(GetWorld(), NotificationsClass);
	if (Notifications != nullptr) Notifications->AddToViewport();
}

void ASurvivalScifi_HUD::ShowInventory()
{
	if (InventoryClass != nullptr) Inventory = CreateWidget<UPlayerInventoryUserWidget>(GetWorld(), InventoryClass);
	if (Inventory != nullptr) Inventory->AddToViewport();
}

void ASurvivalScifi_HUD::HideInventory()
{
	if (Inventory != nullptr) Inventory->RemoveFromParent();
	Inventory = nullptr;
}

void ASurvivalScifi_HUD::ShowInteraction()
{
	if (Interaction == nullptr && InteractionClass != nullptr) 
		Interaction = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), InteractionClass);
	
	if (Interaction != nullptr && !Interaction->IsInViewport())
	{
		Interaction->AddToViewport();
		//UE_LOG(LogTemp, Warning, TEXT("Showing interaction text"));
	}
}

void ASurvivalScifi_HUD::HideInteraction()
{
	if (Interaction != nullptr)
	{
		Interaction->RemoveFromParent();
		Interaction = nullptr;
		//UE_LOG(LogTemp, Warning, TEXT("Hiding interaction text"));
	}
	
}

void ASurvivalScifi_HUD::ResetInteraction()
{
	HideInteraction();
	ShowInteraction();
}

void ASurvivalScifi_HUD::ShowCraftingMenu()
{
	if (CraftingMenu == nullptr && CraftingMenuClass != nullptr)
		CraftingMenu = CreateWidget<UCraftingMenuUserWidget>(GetWorld(), CraftingMenuClass);

	if (CraftingMenu != nullptr && !CraftingMenu->IsInViewport())
		CraftingMenu->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
	GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
}

void ASurvivalScifi_HUD::HideCraftingMenu()
{
	if (CraftingMenu != nullptr)
	{
		CraftingMenu->RemoveFromParent();
		CraftingMenu = nullptr;
	}

	GetOwningPlayerController()->SetShowMouseCursor(false);
	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
}

void ASurvivalScifi_HUD::UpdateCraftingMenu()
{
	if (CraftingMenu != nullptr)
		CraftingMenu->UpdateCraftingScreen();
}

void ASurvivalScifi_HUD::DisplayAddedItems(UItemDataAsset* ItemDataAsset, int Amount)
{
	if (Notifications != nullptr) Notifications->AddedItems(ItemDataAsset, Amount);
	else UE_LOG(LogTemp, Error, TEXT("Missing Notifications reference"));
}

void ASurvivalScifi_HUD::DisplayRemovedItems(UItemDataAsset* ItemDataAsset, int Amount)
{
	if (Notifications != nullptr) Notifications->RemovedItems(ItemDataAsset, Amount);
	else UE_LOG(LogTemp, Error, TEXT("Missing Notifications reference"));
}
