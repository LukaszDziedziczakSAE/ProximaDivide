// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PlayerInventoryUserWidget.h"
#include "UI/InventoryUserWidget.h"
#include "Character/PlayerCharacter.h"
#include "UI/InventoryItemUserWidget.h"
#include "UI/InventorySlotUserWidget.h"
#include "UI/DragUserWidget.h"
#include "Game/SurvivalScifi_DragDropOperation.h"
#include "Item/InventoryComponent.h"

void UPlayerInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryWidget->SetInventory(PlayerCharacter->GetInventoryComponent());
}

bool UPlayerInventoryUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	//FVector2D Postion = InDragDropEvent.GetScreenSpacePosition();
	//UE_LOG(LogTemp, Warning, TEXT("NativeOnDrop %s"), *Postion.ToString());

	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(InOperation);
	if (DragDropOperation != nullptr)
	{
		if (DragDropOperation->ToInventory != nullptr && DragDropOperation->ToInventoryPosition != FIntPoint::ZeroValue)
		{
			if (!DragDropOperation->ToInventory->TryAddItemAt(DragDropOperation->Item, DragDropOperation->ToInventoryPosition))
				UE_LOG(LogTemp, Error, TEXT("Unable to add drag item to new inventory"));
		}

		else if (DragDropOperation->FromInventory != nullptr && DragDropOperation->FromInventoryPosition != FIntPoint::ZeroValue)
		{
			if (!DragDropOperation->FromInventory->TryAddItemAt(DragDropOperation->Item, DragDropOperation->FromInventoryPosition))
				UE_LOG(LogTemp, Error, TEXT("Unable to add drag item to new inventory"));
		}

		
		DragDropOperation->DragUserWidget = nullptr;
	}
	RefreshInventories();
	return result;
}

void UPlayerInventoryUserWidget::RefreshInventories()
{
	InventoryWidget->RefreshSlots();
}
