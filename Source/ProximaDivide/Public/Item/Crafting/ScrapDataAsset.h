// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScrapDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FScrapItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UItemDataAsset* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Amount{ 1 };
};

UCLASS()
class PROXIMADIVIDE_API UScrapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UItemDataAsset* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FScrapItem> ScrapItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BuiltTime{ 1.0f }; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CraftingLaserHeightOffset{ 0.0f };
};
