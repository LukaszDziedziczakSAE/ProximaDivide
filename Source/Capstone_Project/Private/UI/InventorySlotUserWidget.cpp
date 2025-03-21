// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventorySlotUserWidget.h"
#include "Components/SizeBox.h"

void UInventorySlotUserWidget::SetPosition(FIntPoint NewPosition)
{
	Position = NewPosition;
}

void UInventorySlotUserWidget::SetSize(float Size)
{
	SizeBox->SetWidthOverride(Size);
	SizeBox->SetHeightOverride(Size);
}
