// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/PaperdollComponent.h"
#include "Item/EquipableItemDataAsset.h"

// Sets default values for this component's properties
UPaperdollComponent::UPaperdollComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPaperdollComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UPaperdollComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UPaperdollComponent::TryAddEquipable(UEquipableItemDataAsset* Equipable)
{
	if (Slot1.Item == nullptr)
	{
		Slot1.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;
	}

	else if (Slot2.Item == nullptr)
	{
		Slot2.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;
	}

	else if (Slot3.Item == nullptr)
	{
		Slot3.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;
	}

	else if (Slot4.Item == nullptr)
	{
		Slot4.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;
	}

	else if (Slot5.Item == nullptr)
	{
		Slot5.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;
	}

	return false;
}

bool UPaperdollComponent::TryAddEquipableToSlot(UEquipableItemDataAsset* Equipable, int SlotNumber)
{
	switch (SlotNumber)
	{
	case 1:
		Slot1.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;

	case 2:
		Slot2.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;

	case 3:
		Slot3.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;

	case 4:
		Slot4.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;

	case 5:
		Slot5.Item = Equipable;
		OnSlotChange.Broadcast();
		return true;

	default:
		return false;
	}
}

bool UPaperdollComponent::TryRemoveItemFromSlot(int SlotNumber)
{
	switch (SlotNumber)
	{
	case 1:
		Slot1.Item = nullptr;
		OnSlotChange.Broadcast();
		return true;

	case 2:
		Slot2.Item = nullptr;
		OnSlotChange.Broadcast();
		return true;

	case 3:
		Slot3.Item = nullptr;
		OnSlotChange.Broadcast();
		return true;

	case 4:
		Slot4.Item = nullptr;
		OnSlotChange.Broadcast();
		return true;

	case 5:
		Slot5.Item = nullptr;
		OnSlotChange.Broadcast();
		return true;

	default:
		return false;
	}
}

FSlotItem UPaperdollComponent::GetSlot(int SlotNumber)
{
	switch (SlotNumber)
	{
	case 1:
		return Slot1;

	case 2:
		return Slot2;

	case 3:
		return Slot3;

	case 4:
		return Slot4;

	case 5:
		return Slot5;

	default:
		return FSlotItem();
	}
}

FSlotItem UPaperdollComponent::GetCurrentSlot()
{
	return GetSlot(Index);
}

EAnimHandsType UPaperdollComponent::GetCurrentAnimHandsType()
{
	if (Index >= 0 && Index <= 5 && GetCurrentSlot().Item != nullptr)
		return GetCurrentSlot().Item->AnimHandsType;

	return EAnimHandsType::None;
}

void UPaperdollComponent::SelectSlot(int SlotNumber)
{
	if (GetSlot(SlotNumber).Item == nullptr) return;

	if (SlotNumber == Index) Index = 0;
	else Index = SlotNumber;
	OnSlotChange.Broadcast();
}

bool UPaperdollComponent::DoesSlotHaveItem(int SlotNumber)
{
	return Index >= 0 && Index <= 5 && GetSlot(SlotNumber).Item != nullptr;
}

bool UPaperdollComponent::IsCurrentSlotHaveItem()
{
	return Index >= 0 && Index <= 5 && GetCurrentSlot().Item != nullptr;
}

void UPaperdollComponent::CurrentSlotSingleUseItem()
{
	if (Index >= 0 && Index <= 5 && GetCurrentSlot().Item != nullptr)
	{
		int oldSlot = Index;
		Index = 0;
		TryRemoveItemFromSlot(oldSlot);
	}
}

