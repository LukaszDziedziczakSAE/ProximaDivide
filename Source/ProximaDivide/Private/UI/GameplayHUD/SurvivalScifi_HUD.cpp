// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "UI/Inventory/PlayerInventoryUserWidget.h"
#include "UI/Crafting/CraftingMenuUserWidget.h"
#include "UI/Inventory/InventoryItemUserWidget.h"
#include "Item/Crafting/ItemDataAsset.h"
#include "UI/Inventory/InventorySlotUserWidget.h"
#include "UI/Notifications/NotificationsUserWidget.h"
#include "UI/Menus/PauseMenu_UserWidget.h"
#include "UI/Misc/DeathScreenUserWidget.h"
#include "UI/Notifications/TutorialUserWidget.h"
#include "Game/SurvivalScifi_PlayerController.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerTutorialComponent.h"
#include "UI/Misc/TittleCard_UserWidget.h"
#include "UI/Notifications/Objectives_UserWidget.h"
#include "UI/Missions/Missions_UserWidget.h"
#include "UI/Repair/Repair_UserWidget.h"

void ASurvivalScifi_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (NotificationsClass != nullptr) Notifications = CreateWidget<UNotificationsUserWidget>(GetWorld(), NotificationsClass);
	if (Notifications != nullptr) Notifications->AddToViewport();

	ASurvivalScifi_PlayerController* PlayerController = Cast<ASurvivalScifi_PlayerController>(GetOwningPlayerController());
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController reference is nullptr in HUD!"));
		return;
	}

	PlayerCharacter = PlayerController->GetPlayerCharacter();
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter reference is nullptr in HUD!"));
		return;
		
	}

	PlayerTutorialComponent = PlayerCharacter->GetTutorialComponent();

	if (!PlayerCharacter->IsPlayingSequence()) ShowGameHUD();
}

void ASurvivalScifi_HUD::ShowGameHUD()
{
	HideGameHUD();
	if (!IsValid(PlayerTutorialComponent))
	{
		ASurvivalScifi_PlayerController* PlayerController = Cast<ASurvivalScifi_PlayerController>(GetOwningPlayerController());
		if (PlayerController != nullptr)
			PlayerTutorialComponent = PlayerController->GetPlayerCharacter()->GetTutorialComponent();
	}

	if (!IsValid(PlayerTutorialComponent)) return;

	if (PlayerStatsClass != nullptr && !PlayerTutorialComponent->HideStats)
		PlayerStats = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), PlayerStatsClass);
	if (PlayerStats != nullptr) PlayerStats->AddToViewport();

	if (ActionBarClass != nullptr && !PlayerTutorialComponent->HideActionBar) 
		ActionBar = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), ActionBarClass);
	if (ActionBar != nullptr) ActionBar->AddToViewport();

	if (CrosshairClass != nullptr) 
		Crosshair = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), CrosshairClass);
	if (Crosshair != nullptr) Crosshair->AddToViewport();

	if (TutorialClass != nullptr) 
		Tutorial = CreateWidget<UTutorialUserWidget>(GetWorld(), TutorialClass);
	if (Tutorial != nullptr) Tutorial->AddToViewport();

	if (ObjectivesClass != nullptr)
		Objectives = CreateWidget<UObjectives_UserWidget>(GetWorld(), ObjectivesClass);
	if (Objectives != nullptr) Objectives->AddToViewport();
}

void ASurvivalScifi_HUD::HideGameHUD()
{
	if (!IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("HideGameHUD aborted: HUD is not valid at low level."));
		return;
	}

	if (GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HideGameHUD aborted: World is nullptr."));
		return;
	}

	if (GetWorld()->bIsTearingDown)
	{
		UE_LOG(LogTemp, Warning, TEXT("HideGameHUD aborted: World is tearing down."));
		return;
	}

	if (IsPendingKillPending())
	{
		UE_LOG(LogTemp, Warning, TEXT("HideGameHUD aborted: HUD is pending kill."));
		return;
	}
	
	HideInteraction();

	if (IsValid(PlayerStats))
	{
		PlayerStats->RemoveFromParent();
		PlayerStats = nullptr;
	}

	if (IsValid(ActionBar))
	{
		ActionBar->RemoveFromParent();
		ActionBar = nullptr;
	}

	if (IsValid(Crosshair))
	{
		Crosshair->RemoveFromParent();
		Crosshair = nullptr;
	}

	if (IsValid(Tutorial))
	{
		Tutorial->RemoveFromParent();
		Tutorial = nullptr;
	}

	if (IsValid(Objectives))
	{
		Objectives->RemoveFromParent();
		Objectives = nullptr;
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
	if (bSequenceIsPlaying) return;

	if (Interaction == nullptr && InteractionClass != nullptr) 
		Interaction = CreateWidget<USurvivalScifiUserWidget>(GetWorld(), InteractionClass);
	
	if (Interaction != nullptr && !Interaction->IsInViewport())
	{
		Interaction->AddToViewport();
	}
}

void ASurvivalScifi_HUD::HideInteraction()
{
	if (IsValid(Interaction))
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

void ASurvivalScifi_HUD::SequenceStart()
{
	bSequenceIsPlaying = true;
	HideGameHUD();
}

void ASurvivalScifi_HUD::SequeneceEnd()
{
	bSequenceIsPlaying = false;
	ShowGameHUD();
}

void ASurvivalScifi_HUD::ShowTitleCard()
{
	if (TitleCardClass != nullptr) 
		TitleCard = CreateWidget<UTittleCard_UserWidget>(GetWorld(), TitleCardClass);

	if (TitleCard != nullptr) TitleCard->AddToViewport();
}

void ASurvivalScifi_HUD::UpdateObjectives()
{
	if (IsValid(Objectives))
	{
		Objectives->UpdateObjectivesWidget();
	}
}

void ASurvivalScifi_HUD::ShowBlackscreen()
{
	if (BlackscreenClass != nullptr)
		Blackscreen = CreateWidget<UUserWidget>(GetWorld(), BlackscreenClass);

	if (Blackscreen != nullptr) Blackscreen->AddToViewport();
}

void ASurvivalScifi_HUD::ShowMissions()
{
	HideGameHUD();
	if (Missions == nullptr && MissionsClass != nullptr)
		Missions = CreateWidget<UMissions_UserWidget>(GetWorld(), MissionsClass);

	if (Missions != nullptr && !Missions->IsInViewport())
		Missions->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
	GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
}

void ASurvivalScifi_HUD::HideMissions()
{
	if (Missions != nullptr)
	{
		Missions->RemoveFromParent();
		Missions = nullptr;
	}

	GetOwningPlayerController()->SetShowMouseCursor(false);
	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
	ShowGameHUD();
}

void ASurvivalScifi_HUD::ShowRepairPanel()
{
	HideGameHUD();
	if (Repair == nullptr && RepairClass != nullptr)
		Repair = CreateWidget<URepair_UserWidget>(GetWorld(), RepairClass);

	if (Repair != nullptr && !Repair->IsInViewport())
		Repair->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
	GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
}

void ASurvivalScifi_HUD::HideRepairPanel()
{
	if (Repair != nullptr)
	{
		Repair->RemoveFromParent();
		Repair = nullptr;
	}

	GetOwningPlayerController()->SetShowMouseCursor(false);
	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
	ShowGameHUD();
}
