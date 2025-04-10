// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventorySlotUserWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI/SurvivalScifi_HUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/DragUserWidget.h"
#include "Game/SurvivalScifi_DragDropOperation.h"
#include "UI/PlayerInventoryUserWidget.h"
#include "Item/ItemDataAsset.h"

void UInventorySlotUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HUD = GetOwningPlayerPawn()->GetController<APlayerController>()->GetHUD<ASurvivalScifi_HUD>();

	if (HUD == nullptr) UE_LOG(LogTemp, Error, TEXT("Missing HUD reference"));
}

void UInventorySlotUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	PositionInViewport = MyGeometry.LocalToAbsolute(FVector2D::ZeroVector) * UWidgetLayoutLibrary::GetViewportScale(GetWorld());
}

void UInventorySlotUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (HUD != nullptr)
	{
		HUD->MouseOverSlot = this;
		//UE_LOG(LogTemp, Warning, TEXT("Mouse over %s"), *Position.ToString());
	}
}

void UInventorySlotUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (HUD != nullptr)
	{
		if (HUD->MouseOverSlot == this) HUD->MouseOverSlot = nullptr;
		//UE_LOG(LogTemp, Warning, TEXT("Mouse left %s"), *Position.ToString());
	}
}

void UInventorySlotUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(InOperation);
	if (DragDropOperation != nullptr)
	{
		DragDropOperation->ToInventoryPosition = Position;
		DragDropOperation->ToInventory = Inventory;

		PlayerInventoryUserWidget->ShowCanDrop(Inventory, DragDropOperation->Item, Position);
	}
}

void UInventorySlotUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	USurvivalScifi_DragDropOperation* DragDropOperation = Cast<USurvivalScifi_DragDropOperation>(InOperation);
	if (DragDropOperation != nullptr)
	{
		if (DragDropOperation->ToInventoryPosition == Position)
		{
			DragDropOperation->ToInventoryPosition = FIntPoint::ZeroValue;
			DragDropOperation->ToInventory = nullptr;

			PlayerInventoryUserWidget->RemoveCanDrop(Inventory);
		}
	}
}

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
	isOccupied = bIsOccupied;
	ResetToOccupied();
}

void UInventorySlotUserWidget::ResetToOccupied()
{
	CellImage->SetColorAndOpacity(isOccupied ? OccupiedColor : FreeColor);
}

void UInventorySlotUserWidget::ShowCanDropTo()
{
	CellImage->SetColorAndOpacity(isOccupied ? CannotDropColor : CanDropColor);
}
