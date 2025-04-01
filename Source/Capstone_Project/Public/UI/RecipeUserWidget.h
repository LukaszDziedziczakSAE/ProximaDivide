// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "RecipeUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API URecipeUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* RecipeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RecipeNameText;

	UPROPERTY()
	class URecipeDataAsset* Recipe;

public:
	UFUNCTION()
	void Set(URecipeDataAsset* NewRecipe);

	UFUNCTION()
	void OnButtonPress();
};
