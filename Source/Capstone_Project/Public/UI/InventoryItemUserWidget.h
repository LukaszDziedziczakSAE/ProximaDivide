// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UInventoryItemUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY()
	class UItemDataAsset* Item;

public:
	UFUNCTION()
	void Set(UItemDataAsset* ItemData, float CellSize, bool Roated);

	UFUNCTION()
	void Orient(bool IsRotated);
};
