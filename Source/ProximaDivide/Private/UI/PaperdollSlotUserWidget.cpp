// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PaperdollSlotUserWidget.h"
#include "Character/PlayerCharacter.h"
#include "Character/PaperdollComponent.h"
#include "Components/Image.h"
#include "Item/EquipableItemDataAsset.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/DragUserWidget.h"
#include "Game/SurvivalScifi_DragDropOperation.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"


void UPaperdollSlotUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot();

	PlayerCharacter->GetPaperdollComponent()->OnSlotChange.AddDynamic(this, &UPaperdollSlotUserWidget::UpdateSlot);
}

void UPaperdollSlotUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	PlayerCharacter->GetPaperdollComponent()->OnSlotChange.RemoveDynamic(this, &UPaperdollSlotUserWidget::UpdateSlot);
}

void UPaperdollSlotUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	SelectionIndicator->SetColorAndOpacity(SelectedColor);
}

void UPaperdollSlotUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	SelectionIndicator->SetColorAndOpacity(UnselectedColor);
}

FReply UPaperdollSlotUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return EventReply.NativeReply;
}

void UPaperdollSlotUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (PaperdollSlot().Item == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Paperdoll slot item reference missing"));
		return;
	}

	UDragUserWidget* DragUserWidget = CreateWidget<UDragUserWidget>(GetWorld(), DragUserWidgetClass);
	DragUserWidget->Item = PaperdollSlot().Item;
	DragUserWidget->CellSize = CellSize;
	DragUserWidget->Rotated = false;

	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(USurvivalScifi_DragDropOperation::StaticClass()));
	DragDropOperation->DragUserWidget = DragUserWidget;
	DragDropOperation->Item = PaperdollSlot().Item;
	DragDropOperation->CellSize = CellSize;
	DragDropOperation->Rotated = false;
	DragDropOperation->FromSlot = SlotNumber;

	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(DragUserWidget->GetSizeBox()->Slot);
	FVector2D SlotPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	SlotPosition.X -= CellSize / 2;
	SlotPosition.Y -= CellSize / 2;
	CanvasPanelSlot->SetPosition(SlotPosition);

	DragDropOperation->Pivot = EDragPivot::MouseDown;
	DragDropOperation->DefaultDragVisual = DragUserWidget;
	OutOperation = DragDropOperation;

	if (!PlayerCharacter->GetPaperdollComponent()->TryRemoveItemFromSlot(SlotNumber))
		UE_LOG(LogTemp, Error, TEXT("Unabel to remove item for paperdoll slot %d"), SlotNumber);
}

void UPaperdollSlotUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(InOperation);
	if (DragDropOperation != nullptr)
	{
		DragDropOperation->ToSlot = SlotNumber;
		SelectionIndicator->SetColorAndOpacity(SelectedColor);
	}
}

void UPaperdollSlotUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(InOperation);
	if (DragDropOperation != nullptr)
	{
		if (DragDropOperation->ToSlot == SlotNumber)
		{
			DragDropOperation->ToSlot = 0;
			SelectionIndicator->SetColorAndOpacity(UnselectedColor);
		}
	}
}

FSlotItem UPaperdollSlotUserWidget::PaperdollSlot()
{
	switch (SlotNumber)
	{
	case 1:
		return PlayerCharacter->GetPaperdollComponent()->GetSlot1();

	case 2:
		return PlayerCharacter->GetPaperdollComponent()->GetSlot2();

	case 3:
		return PlayerCharacter->GetPaperdollComponent()->GetSlot3();

	case 4:
		return PlayerCharacter->GetPaperdollComponent()->GetSlot4();

	case 5:
		return PlayerCharacter->GetPaperdollComponent()->GetSlot5();

	default:
		return FSlotItem();
	}


	
}

void UPaperdollSlotUserWidget::UpdateSlot()
{
	if (SlotNumber >= 1 && SlotNumber <= 5 && PaperdollSlot().Item != nullptr)
	{
		ItemImage->SetBrushFromTexture(PaperdollSlot().Item->Image, false);
		ItemImage->SetDesiredSizeOverride(FVector2D{ (PaperdollSlot().Item->Size.X * CellSize), (PaperdollSlot().Item->Size.Y * CellSize) });
	}

	else
	{
		ItemImage->SetBrushFromTexture(nullptr, false);
		ItemImage->SetDesiredSizeOverride(FVector2D::ZeroVector);
	}

	bool IsSelected = PlayerCharacter->GetPaperdollComponent()->GetCurrentSlotNumber() == SlotNumber;
	SelectionIndicator->SetColorAndOpacity(IsSelected ? SelectedColor : UnselectedColor);
}
