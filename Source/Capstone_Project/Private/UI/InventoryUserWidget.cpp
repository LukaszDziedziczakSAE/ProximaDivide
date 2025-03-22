// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventoryUserWidget.h"
#include "Item/InventoryComponent.h"
#include "Components/SizeBox.h"
#include "UI/InventorySlotUserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Item/FInventoryItem.h"
#include "UI/InventoryItemUserWidget.h"
#include "Components/Overlay.h"
#include "Item/ItemDataAsset.h"

void UInventoryUserWidget::NativeDestruct()
{
}

void UInventoryUserWidget::SetInventory(UInventoryComponent* Inventory)
{
	InventoryComponent = Inventory;

	SizeBox->SetWidthOverride(InventoryComponent->GetSize().X * CellSize);
	SizeBox->SetHeightOverride(InventoryComponent->GetSize().Y * CellSize);

	if (SlotClass == nullptr) return;

	for (int x = 1; x <= InventoryComponent->GetSize().X; x++)
	{
		for (int y = 1; y <= InventoryComponent->GetSize().Y; y++)
		{
			UInventorySlotUserWidget* InventorySlot = CreateWidget<UInventorySlotUserWidget>(GetWorld(), SlotClass);
			InventorySlot->SetSize(CellSize);
			InventorySlot->SetPosition(FIntPoint(x, y));
			//Grid->AddChildToUniformGrid(InventorySlot, y - 1, x - 1);
			InventoryOverlay->AddChildToOverlay(InventorySlot);
			InventorySlot->SetPadding(FMargin{(x-1)*CellSize, (y-1)*CellSize, 0, 0});
			Slots.Add(InventorySlot);
		}
	}

	if (ItemClass == nullptr) return;

	for (FInventoryItem InventoryItem : InventoryComponent->GetItems())
	{
		UInventoryItemUserWidget* InventoryItemWidget = CreateWidget<UInventoryItemUserWidget>(GetWorld(), ItemClass);
		InventoryOverlay->AddChildToOverlay(InventoryItemWidget);
		//InventoryItemWidget->SetRenderTransformPivot(FVector2D::ZeroVector);

		InventoryItemWidget->Set(InventoryItem.Item, CellSize, InventoryItem.Rotated);

		if (InventoryItem.Rotated)
		{
			InventoryItemWidget->SetPadding(FMargin{
				(InventoryItem.Position.X - 1)* CellSize,
				(InventoryItem.Position.Y - 1)* CellSize,
				0, 0 });
		}
		else
		{
			InventoryItemWidget->SetPadding(FMargin{ 
				(InventoryItem.Position.X - 1) * CellSize, 
				(InventoryItem.Position.Y - 1) * CellSize, 
				0, 0 });
		}

		

		Items.Add(InventoryItemWidget);
	}

	UE_LOG(LogTemp, Warning, TEXT("Slots: %d"), Slots.Num());
}
