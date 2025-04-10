// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventoryItemUserWidget.h"
#include "Components/SizeBox.h"
#include "Item/ItemDataAsset.h"
#include "Components/Image.h"
#include "UI/SurvivalScifi_HUD.h"
#include "UI/PlayerInventoryUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/DragUserWidget.h"
#include "Game/SurvivalScifi_DragDropOperation.h"
#include "Item/InventoryComponent.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryItemUserWidget::Set(UInventoryComponent* FromInventory, UItemDataAsset* ItemData, float NewCellSize, FIntPoint NewPosition, bool Rotated, int NewSlotNumber)
{
	Inventory = FromInventory;
	Item = ItemData;
	bRotated = Rotated;
	CellSize = NewCellSize;
	Position = NewPosition;
	SlotNumber = NewSlotNumber;

	SizeBox->SetHeightOverride(Item->Size.Y * CellSize);
	SizeBox->SetWidthOverride(Item->Size.X * CellSize);

	Orient();
	UpdateImage();

	if (ItemImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing ItemImage reference"), *GetName());
		return;
	}
	//ItemImage->OnMouseButtonDownEvent.BindUFunction(this, FName("OnMouseDown"));
}

void UInventoryItemUserWidget::Rotate()
{
	bRotated = !bRotated;
	Orient();
	UpdateImage();
}

void UInventoryItemUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HUD = GetOwningPlayerPawn()->GetController<APlayerController>()->GetHUD<ASurvivalScifi_HUD>();
	if (HUD != nullptr) PlayerInventoryUserWidget = HUD->GetInventory();

	if (HUD == nullptr) UE_LOG(LogTemp, Error, TEXT("Missing HUD reference"));
}

void UInventoryItemUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	if (HUD != nullptr)
	{
		HUD->MouseOverItem = this;
		//UE_LOG(LogTemp, Warning, TEXT("Mouse over %s"), *Item->Name);
	}
}

void UInventoryItemUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (HUD != nullptr)
	{
		if (HUD->MouseOverItem == this) HUD->MouseOverItem = nullptr;
		//UE_LOG(LogTemp, Warning, TEXT("Mouse left %s"), *Item->Name);
	}
}

FReply UInventoryItemUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return EventReply.NativeReply;
}

void UInventoryItemUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragUserWidget* DragUserWidget = CreateWidget<UDragUserWidget>(GetWorld(), DragUserWidgetClass);
	DragUserWidget->Item = Item;
	DragUserWidget->CellSize = CellSize;
	DragUserWidget->Rotated = bRotated;

	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(USurvivalScifi_DragDropOperation::StaticClass()));
	DragDropOperation->DragUserWidget = DragUserWidget;
	DragDropOperation->Item = Item;
	DragDropOperation->FromInventory = Inventory;
	DragDropOperation->FromInventoryPosition = Position;
	DragDropOperation->CellSize = CellSize;
	DragDropOperation->Rotated = bRotated;

	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(DragUserWidget->GetSizeBox()->Slot);
	FVector2D SlotPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	SlotPosition.X -= CellSize / 2;
	SlotPosition.Y -= CellSize / 2;
	CanvasPanelSlot->SetPosition(SlotPosition);

	DragDropOperation->Pivot = EDragPivot::MouseDown;
	DragDropOperation->DefaultDragVisual = DragUserWidget;

	OutOperation = DragDropOperation;
	if (Inventory->TryRemoveItemAt(Item, Position))
		PlayerInventoryUserWidget->RefreshInventories();
}

void UInventoryItemUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	//UE_LOG(LogTemp, Warning, TEXT("NativeOnDragLeave"));
	//SetVisibility(ESlateVisibility::Visible);
}

void UInventoryItemUserWidget::Orient()
{
	if (ItemImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing ItemImage reference"), *GetName());
		return;
	}
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing Item reference"), *GetName());
		return;
	}

	if (!bRotated)
	{
		ItemImage->SetDesiredSizeOverride(FVector2D{ (Item->Size.X * CellSize), (Item->Size.Y * CellSize) });
	}
	else
	{
		ItemImage->SetDesiredSizeOverride(FVector2D{ (Item->Size.Y * CellSize), (Item->Size.X * CellSize) });
	}
}

void UInventoryItemUserWidget::UpdateImage()
{
	if (ItemImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing ItemImage reference"), *GetName());
		return;
	}
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing Item reference"), *GetName());
		return;
	}

	if (!bRotated)
	{
		ItemImage->SetBrushFromTexture(Item->Image, false);
	}
	else if (bRotated)
	{
		ItemImage->SetBrushFromTexture(Item->ImageRotated, false);
	}
}
