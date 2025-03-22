// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PaperdollSlotUserWidget.h"
#include "Character/PlayerCharacter.h"
#include "Character/PaperdollComponent.h"
#include "Components/Image.h"
#include "Item/EquipableItemDataAsset.h"


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
