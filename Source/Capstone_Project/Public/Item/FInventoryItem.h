// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UItemDataAsset* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIntPoint Position{ 1,1 };
};
