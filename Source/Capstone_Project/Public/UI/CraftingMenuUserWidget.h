// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "UI/RecipeUserWidget.h"
#include "CraftingMenuUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UCraftingMenuUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(meta = (BindWidget))
	class UButton* ResourcesButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SustenanceButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ToolsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URecipeUserWidget> RecipeItemPrefab;

	UPROPERTY(VisibleAnywhere)
	TArray<URecipeUserWidget*> RecipeItems;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* RecipeList;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* CraftingIndicator;

	UPROPERTY()
	class ACraftingMachine* CraftingMachine;

	UPROPERTY(VisibleAnywhere)
	FLinearColor UnselectedColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor SelectedColor;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CraftingStatusText;

	UPROPERTY(meta = (BindWidget))
	class UImage* CircularProgressImage;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ProgressMaterialPrefab;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* ProgressMaterial;

	UFUNCTION()
	void PopulateRecipeList(ECraftingMenuType CraftingMenuType);

	UFUNCTION()
	void OnResourceButtonPress();

	UFUNCTION()
	void OnSustenanceButtonPress();

	UFUNCTION()
	void OnToolsButtonPress();

	UFUNCTION()
	void OnEquipmentButtonPress();

	UFUNCTION()
	void ResetButtonBackgrounds();

	UFUNCTION()
	void ClearRecipeList();

public:
	UFUNCTION()
	void UpdateCraftingScreen();
};
