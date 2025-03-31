// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RecipeDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FRecipeItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UItemDataAsset* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Amount{ 1 };
};

UENUM(BlueprintType)
enum class ECraftingMenuType : uint8
{
	Resource UMETA(DisplayName = "Resource"),
	Sustenance UMETA(DisplayName = "Sustenance"),
	Tool UMETA(DisplayName = "Tool"),
	Equipment UMETA(DisplayName = "Equipment")
};

UCLASS()
class CAPSTONE_PROJECT_API URecipeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UItemDataAsset* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FRecipeItem> RecipeItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BuiltTime{ 1.0f }; // how long it takes to produce

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECraftingMenuType CraftingMenuType;
};
