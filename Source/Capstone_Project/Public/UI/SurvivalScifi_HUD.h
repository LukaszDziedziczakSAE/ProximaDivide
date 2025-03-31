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
	TSubclassOf<class UPlayerInventoryUserWidget> InventoryClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> InteractionClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USurvivalScifiUserWidget> CrosshairClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCraftingMenuUserWidget> CraftingMenuClass;

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

public:
	UFUNCTION(BlueprintCallable)
	void ShowInventory();

	UFUNCTION(BlueprintCallable)
	void HideInventory();

	UFUNCTION(BlueprintPure)
	bool IsShowingInventory() { return Inventory != nullptr; }

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

	UFUNCTION(BlueprintPure)
	bool IsShowingCraftingMenu() { return CraftingMenu != nullptr; }
};
