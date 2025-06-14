// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SurvivalScifi_HUD.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASurvivalScifi_HUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USurvivalScifiUserWidget> PlayerStatsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> ActionBarClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPlayerInventoryUserWidget> InventoryClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> InteractionClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> CrosshairClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCraftingMenuUserWidget> CraftingMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNotificationsUserWidget> NotificationsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPauseMenu_UserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDeathScreenUserWidget> DeathScreenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTutorialUserWidget> TutorialClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTittleCard_UserWidget> TitleCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UObjectives_UserWidget> ObjectivesClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> BlackscreenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMissions_UserWidget> MissionsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URepair_UserWidget> RepairClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* PlayerStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* ActionBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlayerInventoryUserWidget* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* Interaction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USurvivalScifiUserWidget* Crosshair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCraftingMenuUserWidget* CraftingMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNotificationsUserWidget* Notifications;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPauseMenu_UserWidget* PauseMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDeathScreenUserWidget* DeathScreen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTutorialUserWidget* Tutorial;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerTutorialComponent* PlayerTutorialComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTittleCard_UserWidget* TitleCard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UObjectives_UserWidget* Objectives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* Blackscreen;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMissions_UserWidget* Missions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URepair_UserWidget* Repair;

public:
	UFUNCTION()
	void ShowGameHUD();

	UFUNCTION()
	void HideGameHUD();

	UFUNCTION(BlueprintCallable)
	void ShowInventory();

	UFUNCTION(BlueprintCallable)
	void HideInventory();

	UFUNCTION(BlueprintPure)
	bool IsShowingInventory() { return Inventory != nullptr; }

	UFUNCTION(BlueprintPure)
	UPlayerInventoryUserWidget* GetInventory() { return Inventory; }

	UFUNCTION()
	void ShowInteraction();

	UFUNCTION()
	void HideInteraction();

	UFUNCTION(BlueprintPure)
	bool IsShowingInteraction(){ return Interaction != nullptr; }

	UFUNCTION()
	void ResetInteraction();

	UFUNCTION()
	void ShowCraftingMenu();

	UFUNCTION()
	void HideCraftingMenu();

	UFUNCTION()
	void HideCraftingMenuOnly();

	UFUNCTION(BlueprintPure)
	bool IsShowingCraftingMenu() { return CraftingMenu != nullptr; }

	UFUNCTION()
	void UpdateCraftingMenu();

	UFUNCTION()
	void DisplayAddedItems(class UItemDataAsset* ItemDataAsset, int Amount = 1);

	UFUNCTION()
	void DisplayRemovedItems(class UItemDataAsset* ItemDataAsset, int Amount = 1);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventorySlotUserWidget* MouseOverSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryItemUserWidget* MouseOverItem;

	UFUNCTION()
	void ShowPauseMenu();

	UFUNCTION()
	void HidePauseMenu();

	UFUNCTION(BlueprintPure)
	bool IsShowingPauseMenu() { return PauseMenu != nullptr; }

	UFUNCTION()
	void ShowDeathScreen();

	UFUNCTION()
	void HideDeathScreen();

	UFUNCTION(BlueprintPure)
	bool IsShowingDeathScreen() { return DeathScreen != nullptr; }

	UFUNCTION()
	void UpdateTutorialInfo();

	UFUNCTION()
	void SequenceStart();

	UFUNCTION()
	void SequeneceEnd();

	UFUNCTION(BlueprintCallable)
	void ShowTitleCard();

	UFUNCTION()
	void UpdateObjectives();

	UFUNCTION()
	void ShowBlackscreen();	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bSequenceIsPlaying;

	UFUNCTION()
	void ShowMissions();

	UFUNCTION()
	void HideMissions();

	UFUNCTION(BlueprintPure)
	bool IsShowingMissions() { return Missions != nullptr; }

	UFUNCTION()
	void ShowRepairPanel();

	UFUNCTION()
	void HideRepairPanel();

	UFUNCTION(BlueprintPure)
	bool IsShowingRepairPanel() { return Repair != nullptr; }
};
