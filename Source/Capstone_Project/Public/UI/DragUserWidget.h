// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "DragUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UDragUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemDataAsset* Item;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryItemUserWidget* InventoryItemUserWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D DragOffset;
	
};
