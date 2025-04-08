// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/DragUserWidget.h"
#include "Components/Image.h"
#include "UI/InventoryItemUserWidget.h"
#include "Item/ItemDataAsset.h"
#include "Components/SizeBox.h"

void UDragUserWidget::NativeConstruct()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
	ItemImage->SetBrushFromTexture(Item->Image);
	SizeBox->SetHeightOverride(Item->Size.Y * CellSize);
	SizeBox->SetWidthOverride(Item->Size.X * CellSize);
}
