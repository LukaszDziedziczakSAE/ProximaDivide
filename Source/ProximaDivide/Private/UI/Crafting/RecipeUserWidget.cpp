// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Crafting/RecipeUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Item/Crafting/RecipeDataAsset.h"
#include "Item/Crafting/ItemDataAsset.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerInteractionComponent.h"
#include "Enviroment/CraftingMachine.h"

void URecipeUserWidget::Set(URecipeDataAsset* NewRecipe, bool IsAvailable)
{
	Recipe = NewRecipe;
	RecipeNameText->SetText(FText::FromString(Recipe->Item->Name));

	RecipeButton->SetBackgroundColor(IsAvailable ? UnselectedColor : UnavailableColor);
	if (IsAvailable) RecipeButton->OnClicked.AddDynamic(this, &URecipeUserWidget::OnButtonPress);
}

void URecipeUserWidget::OnButtonPress()
{
	PlayerCharacter->GetPlayerInteractionComponent()->GetCraftingMachine()->Craft(Recipe);
}
