// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventoryItemUserWidget.h"
#include "Components/SizeBox.h"
#include "Item/ItemDataAsset.h"
#include "Components/Image.h"

void UInventoryItemUserWidget::Set(UItemDataAsset* ItemData, float CellSize, bool Roated)
{
	Item = ItemData;

	ItemImage->SetBrushFromTexture(ItemData->Image, false);
	//ItemImage->SetBrushSize(FVector2D{ ItemData->Size.X * CellSize, ItemData->Size.Y * CellSize });
	ItemImage->SetDesiredSizeOverride(FVector2D{ (ItemData->Size.X * CellSize), (ItemData->Size.Y * CellSize) });

	Orient(Roated);
}

void UInventoryItemUserWidget::Orient(bool IsRotated)
{
	

	if (IsRotated)
	{
		double y = Item->Size.X;
		SetRenderTransformAngle(-90);
		//SetRenderTranslation(FVector2D{ 0, y });
	}

	else
	{
		SetRenderTransformAngle(0);
		//SetRenderTranslation(FVector2D{ 0,0 });
	}
}
