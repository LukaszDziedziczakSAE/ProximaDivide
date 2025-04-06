// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventorySlotUserWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventorySlotUserWidget::SetPosition(FIntPoint NewPosition)
{
	Position = NewPosition;

	Cords->SetText(FText::FromString(FString::FromInt(NewPosition.X) + " , " + FString::FromInt(NewPosition.Y)));
}

void UInventorySlotUserWidget::SetSize(float Size)
{
	SizeBox->SetWidthOverride(Size);
	SizeBox->SetHeightOverride(Size);
}

void UInventorySlotUserWidget::SetOccupied(bool bIsOccupied)
{
	CellImage->SetColorAndOpacity(bIsOccupied ? OccupiedColor : FreeColor);
}
