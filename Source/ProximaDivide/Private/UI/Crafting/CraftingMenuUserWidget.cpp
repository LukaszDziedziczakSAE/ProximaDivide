// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Crafting/CraftingMenuUserWidget.h"
#include "Components/Button.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerInteractionComponent.h"
#include "Enviroment/CraftingMachine.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Item/Crafting/RecipeDataAsset.h"
#include "Item/Crafting/ItemDataAsset.h"

void UCraftingMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResourcesButton->OnClicked.AddDynamic(this, &UCraftingMenuUserWidget::OnResourceButtonPress);
	SustenanceButton->OnClicked.AddDynamic(this, &UCraftingMenuUserWidget::OnSustenanceButtonPress);
	ToolsButton->OnClicked.AddDynamic(this, &UCraftingMenuUserWidget::OnToolsButtonPress);
	EquipmentButton->OnClicked.AddDynamic(this, &UCraftingMenuUserWidget::OnEquipmentButtonPress);

	UnselectedColor = ResourcesButton->GetBackgroundColor();

	CraftingMachine = GetOwningPlayerPawn<APlayerCharacter>()->GetPlayerInteractionComponent()->GetCraftingMachine();

	if (CraftingMachine == nullptr) UE_LOG(LogTemp, Error, TEXT("Missing Crafting Machine refernce"));

	UpdateCraftingScreen();

	ProgressMaterial = UMaterialInstanceDynamic::Create(ProgressMaterialPrefab, this);
}

void UCraftingMenuUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (CraftingMachine != nullptr 
		&& CraftingMachine->GetCraftingMachineState() == ECraftingMachineState::Crafting)
	{
		CraftingStatusText->SetText(CraftingMachine->CraftingStatusText());

		ProgressMaterial->SetScalarParameterValue(TEXT("Percentage"), CraftingMachine->GetProgress());
		CircularProgressImage->SetBrushFromMaterial(ProgressMaterial);
	}
}

void UCraftingMenuUserWidget::OnResourceButtonPress()
{
	PopulateRecipeList(ECraftingMenuType::Resource);

	ResetButtonBackgrounds();
	ResourcesButton->SetBackgroundColor(SelectedColor);
}

void UCraftingMenuUserWidget::OnSustenanceButtonPress()
{
	PopulateRecipeList(ECraftingMenuType::Sustenance);

	ResetButtonBackgrounds();
	SustenanceButton->SetBackgroundColor(SelectedColor);
}

void UCraftingMenuUserWidget::OnToolsButtonPress()
{
	PopulateRecipeList(ECraftingMenuType::Tool);

	ResetButtonBackgrounds();
	ToolsButton->SetBackgroundColor(SelectedColor);
}

void UCraftingMenuUserWidget::OnEquipmentButtonPress()
{
	PopulateRecipeList(ECraftingMenuType::Equipment);

	ResetButtonBackgrounds();
	EquipmentButton->SetBackgroundColor(SelectedColor);
}

void UCraftingMenuUserWidget::ResetButtonBackgrounds()
{
	ResourcesButton->SetBackgroundColor(UnselectedColor);
	SustenanceButton->SetBackgroundColor(UnselectedColor);
	ToolsButton->SetBackgroundColor(UnselectedColor);
	EquipmentButton->SetBackgroundColor(UnselectedColor);
}

void UCraftingMenuUserWidget::ClearRecipeList()
{
	if (RecipeItems.Num() > 0)
	{
		for (URecipeUserWidget* Item : RecipeItems)
		{
			Item->RemoveFromParent();
		}
		RecipeItems.Empty();
	}

	ResetButtonBackgrounds();
}

void UCraftingMenuUserWidget::UpdateCraftingScreen()
{
	if (CraftingMachine->GetCraftingMachineState() == ECraftingMachineState::Crafting)
	{
		CraftingStatusText->SetVisibility(ESlateVisibility::Visible);
		CraftingIndicator->SetVisibility(ESlateVisibility::Visible);
		MainMenu->SetVisibility(ESlateVisibility::Collapsed);
		RecipeList->SetVisibility(ESlateVisibility::Collapsed);
	}

	else if (CraftingMachine->GetCraftingMachineState() == ECraftingMachineState::Standby)
	{
		CraftingStatusText->SetVisibility(ESlateVisibility::Collapsed);
		CraftingIndicator->SetVisibility(ESlateVisibility::Collapsed);
		MainMenu->SetVisibility(ESlateVisibility::Visible);
		RecipeList->SetVisibility(ESlateVisibility::Visible);
		ClearRecipeList();
	}

	else
	{
		CraftingStatusText->SetVisibility(ESlateVisibility::Collapsed);
		CraftingIndicator->SetVisibility(ESlateVisibility::Collapsed);
		MainMenu->SetVisibility(ESlateVisibility::Collapsed);
		RecipeList->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCraftingMenuUserWidget::PopulateRecipeList(ECraftingMenuType CraftingMenuType)
{
	ClearRecipeList();

	for (URecipeDataAsset* Recipe : CraftingMachine->GetRecipesByType(CraftingMenuType))
	{
		UE_LOG(LogTemp, Log, TEXT("Creating URecipeUserWidget for %s"), *Recipe->Item->Name);
		URecipeUserWidget* RecipeWidget = CreateWidget<URecipeUserWidget>(GetWorld(), RecipeItemPrefab);
		RecipeWidget->Set(Recipe, CraftingMachine->GetInventory()->CanAfford(Recipe) && CraftingMachine->GetInventory()->CanAddItem(Recipe->Item));
		RecipeItems.Add(RecipeWidget);
		RecipeList->AddChildToVerticalBox(RecipeWidget);
	}
}
