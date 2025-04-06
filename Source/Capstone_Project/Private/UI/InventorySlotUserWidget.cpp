// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/InventorySlotUserWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI/SurvivalScifi_HUD.h"

void UInventorySlotUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HUD = GetOwningPlayerPawn()->GetController<APlayerController>()->GetHUD<ASurvivalScifi_HUD>();

	if (HUD == nullptr) UE_LOG(LogTemp, Error, TEXT("Missing HUD reference"));
}

void UInventorySlotUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (HUD != nullptr)
	{
		HUD->MouseOverSlot = this;
		UE_LOG(LogTemp, Warning, TEXT("Mouse over %s"), *Position.ToString());
	}
}

void UInventorySlotUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (HUD != nullptr)
	{
		if (HUD->MouseOverSlot == this) HUD->MouseOverSlot = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Mouse left %s"), *Position.ToString());
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
	CellImage->SetColorAndOpacity(bIsOccupied ? OccupiedColor : FreeColor);
}
