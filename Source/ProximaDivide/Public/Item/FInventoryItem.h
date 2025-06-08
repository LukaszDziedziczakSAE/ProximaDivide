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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool Rotated;

	TArray<FIntPoint> OccupiedSlots();

	TArray<FIntPoint> OccupiedSlotsRotated();

	TArray<FIntPoint> GetOccupiedSlots() { return Rotated ? OccupiedSlotsRotated() : OccupiedSlots(); }

	inline bool operator==(const FInventoryItem& OtherInventoryItem);
};
