// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PlayerInventoryUserWidget.h"
#include "UI/InventoryUserWidget.h"
#include "Character/PlayerCharacter.h"
#include "UI/InventoryItemUserWidget.h"
#include "UI/InventorySlotUserWidget.h"
#include "UI/DragUserWidget.h"
#include "Game/SurvivalScifi_DragDropOperation.h"
#include "Item/InventoryComponent.h"
#include "Character/PaperdollComponent.h"
#include "Item/EquipableItemDataAsset.h"
#include "Character/PlayerInteractionComponent.h"
#include "Enviroment/Container.h"

void UPlayerInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryWidget->SetInventory(PlayerCharacter->GetInventoryComponent(), this);

	if (PlayerCharacter->GetPlayerInteractionComponent()->GetContainer() != nullptr)
	{
		ContainerInventoryWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ContainerInventoryWidget->SetInventory(PlayerCharacter->GetPlayerInteractionComponent()->GetContainer()->GetInventoryComponent(), this);
	}
	else
	{
		ContainerInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

}

bool UPlayerInventoryUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(InOperation);
	if (DragDropOperation != nullptr)
	{
		UEquipableItemDataAsset* EquipableItem = Cast<UEquipableItemDataAsset>(DragDropOperation->Item);

		if (DragDropOperation->ToInventory != nullptr && DragDropOperation->ToInventoryPosition != FIntPoint::ZeroValue && DragDropOperation->ToSlot == 0)
		{
			if (!DragDropOperation->ToInventory->TryAddItemAt(DragDropOperation->Item, DragDropOperation->ToInventoryPosition))
				UE_LOG(LogTemp, Error, TEXT("Unable to add drag item to new inventory"));
		}

		else if (EquipableItem != nullptr && DragDropOperation->ToSlot > 0 && DragDropOperation->ToSlot <= 5 && DragDropOperation->ToInventory == nullptr)
		{
			if (!PlayerCharacter->GetPaperdollComponent()->TryAddEquipableToSlot(EquipableItem, DragDropOperation->ToSlot))
				UE_LOG(LogTemp, Error, TEXT("Unable to add drag item to new paperdoll slot"));
		}

		else if (EquipableItem != nullptr && DragDropOperation->FromInventory == nullptr && DragDropOperation->FromSlot > 0 && DragDropOperation->FromSlot <= 5)
		{
			if (!PlayerCharacter->GetPaperdollComponent()->TryAddEquipableToSlot(EquipableItem, DragDropOperation->FromSlot))
				UE_LOG(LogTemp, Error, TEXT("Unable to add drag item to old paperdoll slot"));
		}

		else if (DragDropOperation->FromInventory != nullptr && DragDropOperation->FromInventoryPosition != FIntPoint::ZeroValue)
		{
			if (!DragDropOperation->FromInventory->TryAddItemAt(DragDropOperation->Item, DragDropOperation->FromInventoryPosition))
				UE_LOG(LogTemp, Error, TEXT("Unable to add drag item to old inventory"));
		}

		
		DragDropOperation->DragUserWidget = nullptr;
	}
	RefreshInventories();
	return result;
}

void UPlayerInventoryUserWidget::RefreshInventories()
{
	InventoryWidget->RefreshSlots();

	if (ContainerInventoryWidget->Visibility != ESlateVisibility::Collapsed)
		ContainerInventoryWidget->RefreshSlots();
}

void UPlayerInventoryUserWidget::ShowCanDrop(UInventoryComponent* InventoryComponent, UItemDataAsset* Item, FIntPoint Position)
{
	if (InventoryComponent == InventoryWidget->GetInventory())
	{
		InventoryWidget->ShowAvailability(Item, Position);
	}

	else if (InventoryComponent == ContainerInventoryWidget->GetInventory())
	{
		ContainerInventoryWidget->ShowAvailability(Item, Position);
	}
}

void UPlayerInventoryUserWidget::RemoveCanDrop(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent == InventoryWidget->GetInventory())
	{
		InventoryWidget->ResetSlotsToOccupancy();
	}

	else if (InventoryComponent == ContainerInventoryWidget->GetInventory())
	{
		ContainerInventoryWidget->ResetSlotsToOccupancy();
	}
}
