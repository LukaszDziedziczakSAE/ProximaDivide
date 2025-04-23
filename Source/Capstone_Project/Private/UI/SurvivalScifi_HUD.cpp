// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/SurvivalScifi_HUD.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "UI/PlayerInventoryUserWidget.h"
#include "UI/CraftingMenuUserWidget.h"
#include "UI/InventoryItemUserWidget.h"
#include "Item/ItemDataAsset.h"
#include "UI/InventorySlotUserWidget.h"
#include "UI/NotificationsUserWidget.h"
#include "UI/PauseMenu_UserWidget.h"
#include "UI/DeathScreenUserWidget.h"
#include "UI/TutorialUserWidget.h"

void ASurvivalScifi_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (NotificationsClass != nullptr) Notifications = CreateWidget<UNotificationsUserWidget>(GetWorld(), NotificationsClass);
	if (Notifications != nullptr) Notifications->AddToViewport();

	//ShowGameHUD();
}

void ASurvivalScifi_HUD::ShowGameHUD()
{
	HideGameHUD();

	if (PlayerStatsClass != nullptr) PlayerStats = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), PlayerStatsClass);
	if (PlayerStats != nullptr) PlayerStats->AddToViewport();

	if (ActionBarClass != nullptr) ActionBar = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), ActionBarClass);
	if (ActionBar != nullptr) ActionBar->AddToViewport();

	if (CrosshairClass != nullptr) Crosshair = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), CrosshairClass);
	if (Crosshair != nullptr) Crosshair->AddToViewport();

	if (TutorialClass != nullptr) Tutorial = CreateWidget<UTutorialUserWidget>(GetWorld(), TutorialClass);
	if (Tutorial != nullptr) Tutorial->AddToViewport();
}

void ASurvivalScifi_HUD::HideGameHUD()
{
	if (PlayerStats != nullptr)
	{
		PlayerStats->RemoveFromParent();
		PlayerStats = nullptr;
	}

	if (ActionBar != nullptr)
	{
		ActionBar->RemoveFromParent();
		ActionBar = nullptr;
	}

	if (Crosshair != nullptr)
	{
		Crosshair->RemoveFromParent();
		Crosshair = nullptr;
	}

	if (Tutorial != nullptr)
	{
		Tutorial->RemoveFromParent();
		Tutorial = nullptr;
	}
}

void ASurvivalScifi_HUD::ShowInventory()
{
	HideGameHUD();
	if (InventoryClass != nullptr) Inventory = CreateWidget<UPlayerInventoryUserWidget>(GetWorld(), InventoryClass);
	if (Inventory != nullptr) Inventory->AddToViewport();
}

void ASurvivalScifi_HUD::HideInventory()
{
	if (Inventory != nullptr) Inventory->RemoveFromParent();
	Inventory = nullptr;
	ShowGameHUD();
}

void ASurvivalScifi_HUD::ShowInteraction()
{
	if (Interaction == nullptr && InteractionClass != nullptr) 
		Interaction = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), InteractionClass);
	
	if (Interaction != nullptr && !Interaction->IsInViewport())
	{
		Interaction->AddToViewport();
	}
}

void ASurvivalScifi_HUD::HideInteraction()
{
	if (Interaction != nullptr)
	{
		Interaction->RemoveFromParent();
		Interaction = nullptr;
	}
	
}

void ASurvivalScifi_HUD::ResetInteraction()
{
	HideInteraction();
	ShowInteraction();
}

void ASurvivalScifi_HUD::ShowCraftingMenu()
{

	HideGameHUD();
	if (CraftingMenu == nullptr && CraftingMenuClass != nullptr)
		CraftingMenu = CreateWidget<UCraftingMenuUserWidget>(GetWorld(), CraftingMenuClass);

	if (CraftingMenu != nullptr && !CraftingMenu->IsInViewport())
		CraftingMenu->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
	GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
}

void ASurvivalScifi_HUD::HideCraftingMenu()
{
	HideCraftingMenuOnly();

	GetOwningPlayerController()->SetShowMouseCursor(false);
	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
	ShowGameHUD();
}

void ASurvivalScifi_HUD::HideCraftingMenuOnly()
{
	if (CraftingMenu != nullptr)
	{
		CraftingMenu->RemoveFromParent();
		CraftingMenu = nullptr;
	}
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

void ASurvivalScifi_HUD::ShowPauseMenu()
{
	if (PauseMenuClass != nullptr)
		PauseMenu = CreateWidget<UPauseMenu_UserWidget>(GetWorld(), PauseMenuClass);
	if (PauseMenu != nullptr) PauseMenu->AddToViewport();
}

void ASurvivalScifi_HUD::HidePauseMenu()
{
	if (PauseMenu != nullptr)
	{
		PauseMenu->RemoveFromParent();
		PauseMenu = nullptr;
	}
}

void ASurvivalScifi_HUD::ShowDeathScreen()
{
	if (DeathScreenClass != nullptr)
		DeathScreen = CreateWidget<UDeathScreenUserWidget>(GetWorld(), DeathScreenClass);
	if (DeathScreen != nullptr) DeathScreen->AddToViewport();
}

void ASurvivalScifi_HUD::HideDeathScreen()
{
	if (DeathScreen != nullptr)
	{
		DeathScreen->RemoveFromParent();
		DeathScreen = nullptr;
	}
}

void ASurvivalScifi_HUD::UpdateTutorialInfo()
{
	if (Tutorial != nullptr)
		Tutorial->UpdateTutorialInfo();

	if (Inventory != nullptr)
		Inventory->UpdateTutorialInfo();
}
