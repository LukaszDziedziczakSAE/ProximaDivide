// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventoryItemUserWidget.h"
#include "Components/SizeBox.h"
#include "Item/ItemDataAsset.h"
#include "Components/Image.h"

void UInventoryItemUserWidget::Set(UItemDataAsset* ItemData, float CellSize)
{
	//SizeBox->SetWidthOverride(ItemData->Size.X * CellSize);
	//SizeBox->SetHeightOverride(ItemData->Size.Y * CellSize);

	ItemImage->SetBrushFromTexture(ItemData->Image, false);
	ItemImage->SetBrushSize(FVector2D{ ItemData->Size.X * CellSize, ItemData->Size.Y * CellSize });
	ItemImage->SetDesiredSizeOverride(FVector2D{ (ItemData->Size.X * CellSize), (ItemData->Size.Y * CellSize) });
}
