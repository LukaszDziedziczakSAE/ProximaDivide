// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Inventory/InventoryUserWidget.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Components/SizeBox.h"
#include "UI/Inventory/InventorySlotUserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Item/Inventory/FInventoryItem.h"
#include "UI/Inventory/InventoryItemUserWidget.h"
#include "Components/Overlay.h"
#include "Item/Crafting/ItemDataAsset.h"

void UInventoryUserWidget::NativeDestruct()
{
	ClearSlots();
}

void UInventoryUserWidget::SetInventory(UInventoryComponent* Inventory, UPlayerInventoryUserWidget* Widget)
{
	PlayerInventoryUserWidget = Widget;
	InventoryComponent = Inventory;

	SizeBox->SetWidthOverride(InventoryComponent->GetSize().X * CellSize);
	SizeBox->SetHeightOverride(InventoryComponent->GetSize().Y * CellSize);

	RefreshSlots();
}

void UInventoryUserWidget::RefreshSlots()
{
	ClearSlots();

	if (SlotClass == nullptr) return;

	for (int y = 1; y <= InventoryComponent->GetSize().Y; y++)
	{
		for (int x = 1; x <= InventoryComponent->GetSize().X; x++)
		{
			UInventorySlotUserWidget* InventorySlot = CreateWidget<UInventorySlotUserWidget>(GetWorld(), SlotClass);
			InventorySlot->SetSize(CellSize);
			InventorySlot->SetPosition(FIntPoint(x, y));
			InventorySlot->Inventory = InventoryComponent;
			InventorySlot->PlayerInventoryUserWidget = PlayerInventoryUserWidget;
			//Grid->AddChildToUniformGrid(InventorySlot, y - 1, x - 1);
			InventoryOverlay->AddChildToOverlay(InventorySlot);
			InventorySlot->SetPadding(FMargin{ (x - 1) * CellSize, (y - 1) * CellSize, 0, 0 });
			InventorySlot->SetOccupied(InventoryComponent->SlotIsOccupied(FIntPoint(x, y)));
			Slots.Add(InventorySlot);
		}
	}

	if (ItemClass == nullptr) return;

	for (FInventoryItem InventoryItem : InventoryComponent->GetItems())
	{
		UInventoryItemUserWidget* InventoryItemWidget = CreateWidget<UInventoryItemUserWidget>(GetWorld(), ItemClass);
		InventoryItemWidget->Set(InventoryComponent, InventoryItem.Item, CellSize, InventoryItem.Position, InventoryItem.Rotated);

		InventoryOverlay->AddChildToOverlay(InventoryItemWidget);
		InventoryItemWidget->SetPadding(FMargin{
				(InventoryItem.Position.X - 1) * CellSize,
				(InventoryItem.Position.Y - 1) * CellSize,
				0, 0 });
		Items.Add(InventoryItemWidget);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Slots: %d"), Slots.Num());
}

void UInventoryUserWidget::ClearSlots()
{
	if (Slots.Num() > 0)
	{
		for (UInventorySlotUserWidget* SlotWidget : Slots)
		{
			SlotWidget->RemoveFromParent();
		}
		Slots.Empty();
	}

	if (Items.Num() > 0)
	{
		for (UInventoryItemUserWidget* ItemWidget : Items)
		{
			ItemWidget->RemoveFromParent();
		}
		Items.Empty();
	}
}

void UInventoryUserWidget::ResetSlotsToOccupancy()
{
	for (UInventorySlotUserWidget* SlotWidget : Slots)
		SlotWidget->ResetToOccupied();
}

void UInventoryUserWidget::ShowAvailability(UItemDataAsset* Item, FIntPoint Position)
{
	//UE_LOG(LogTemp, Warning, TEXT("Showing availiability for %s"), *Item->Name);
	ResetSlotsToOccupancy();

	TArray<FIntPoint> Footprint;

	for (int y = 0; y < Item->Size.Y; y++)
	{
		for (int x = 0; x < Item->Size.X; x++)
		{
			FIntPoint SlotCord = Position;
			SlotCord.X += x;
			SlotCord.Y += y;
			Footprint.Add(SlotCord);
		}
	}

	for (UInventorySlotUserWidget* SlotWidget : Slots)
	{
		if (Footprint.Contains(SlotWidget->GetPosition()))
		{
			SlotWidget->ShowCanDropTo();
		}
	}
}
