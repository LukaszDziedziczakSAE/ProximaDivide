// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventoryItemUserWidget.h"
#include "Components/SizeBox.h"
#include "Item/ItemDataAsset.h"
#include "Components/Image.h"
#include "UI/SurvivalScifi_HUD.h"
#include "UI/PlayerInventoryUserWidget.h"

void UInventoryItemUserWidget::Set(UItemDataAsset* ItemData, float NewCellSize, bool Rotated, FIntPoint NewPosition, int NewSlotNumber)
{
	Item = ItemData;
	bRotated = Rotated;
	CellSize = NewCellSize;
	Position = NewPosition;
	SlotNumber = NewSlotNumber;

	Orient();
	UpdateImage();

	if (ItemImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing ItemImage reference"), *GetName());
		return;
	}
	ItemImage->OnMouseButtonDownEvent.BindUFunction(this, FName("OnMouseDown"));
}

void UInventoryItemUserWidget::Rotate()
{
	bRotated = !bRotated;
	Orient();
	UpdateImage();
}

void UInventoryItemUserWidget::OnMouseDown()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked %s"), *Item->Name);

	if (PlayerInventoryUserWidget != nullptr) PlayerInventoryUserWidget->
		SetInHand(Item, CellSize, bRotated, Position, SlotNumber);
}

void UInventoryItemUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerInventoryUserWidget = GetOwningPlayerPawn()->GetController<APlayerController>()->GetHUD<ASurvivalScifi_HUD>()->GetInventory();
}

void UInventoryItemUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("Mouse over %s"), *Item->Name);
}

void UInventoryItemUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("Mouse left %s"), *Item->Name);
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
