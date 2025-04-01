// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/RecipeUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Item/RecipeDataAsset.h"
#include "Item/ItemDataAsset.h"
#include "Character/PlayerCharacter.h"
#include "Character/PlayerInteractionComponent.h"
#include "Enviroment/CraftingMachine.h"

void URecipeUserWidget::Set(URecipeDataAsset* NewRecipe)
{
	Recipe = NewRecipe;
	RecipeNameText->SetText(FText::FromString(Recipe->Item->Name));

	RecipeButton->OnClicked.AddDynamic(this, &URecipeUserWidget::OnButtonPress);
}

void URecipeUserWidget::OnButtonPress()
{
	PlayerCharacter->GetPlayerInteractionComponent()->GetCraftingMachine()->Craft(Recipe);
}
