// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PlayerInventoryUserWidget.h"
#include "UI/InventoryUserWidget.h"
#include "Character/PlayerCharacter.h"
#include "UI/InventoryItemUserWidget.h"
#include "UI/SurvivalScifi_HUD.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"

void UPlayerInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Constructing Player Inventory Widget"));

	InventoryWidget->SetInventory(PlayerCharacter->GetInventoryComponent());

	if (TestItem != nullptr) SetInHand(TestItem, 100.0f);
}

void UPlayerInventoryUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (InHand->Visibility == ESlateVisibility::Visible)
	{
		FVector2D MousePosition;
		PlayerCharacter->GetController<APlayerController>()->GetMousePosition(MousePosition.X, MousePosition.Y);
		//InHand->SetPositionInViewport(MousePosition);
		//InHand->SetRenderTranslation(MousePosition);


		//UE_LOG(LogTemp, Warning, TEXT("Setting InHand position %s"), *InHand->Pan);
	}
}

void UPlayerInventoryUserWidget::SetInHand(UItemDataAsset* ItemData, float NewCellSize, bool Rotated, FIntPoint NewPosition, int NewSlotNumber)
{
	InHand->SetVisibility(ESlateVisibility::Visible);
	InHand->Set(ItemData, NewCellSize, Rotated, NewPosition, NewSlotNumber);
}
