// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/InventoryComponent.h"

#include "Item/ItemDataAsset.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


TArray<FIntPoint> UInventoryComponent::Slots()
{
	TArray<FIntPoint> Slots;

	for (int x = 1; x <= Size.X; x++)
	{
		for (int y = 1; y <= Size.Y; y++)
		{
			Slots.Add(FIntPoint{ x,y });
		}
	}

	return Slots;
}

TArray<FIntPoint> UInventoryComponent::GetOccupiedSlots()
{
	TArray<FIntPoint> OccupiedSlots;

	for (FInventoryItem Item : Items)
	{
		for (FIntPoint Slot : Item.GetOccupiedSlots())
			OccupiedSlots.Add(Slot);
	}

	return OccupiedSlots;
}

TArray<FIntPoint> UInventoryComponent::GetAvailableSlotsFor(UItemDataAsset* DataAsset)
{
	TArray<FIntPoint> AvailableSlots;
	TArray<FIntPoint> OccupiedSlots = GetOccupiedSlots();

	for (FIntPoint Slot : Slots())
	{
		if (ItemCanFitInSlot(Slot, DataAsset, OccupiedSlots))
			AvailableSlots.Add(Slot);
	}

	return AvailableSlots;
}

bool UInventoryComponent::ItemCanFitInSlot(FIntPoint Slot, UItemDataAsset* Item, TArray<FIntPoint> OccupiedSlots)
{
	if (!SlotIsValid(Slot))
	{
		UE_LOG(LogTemp, Error, TEXT("Item cannot fit slot invlaid"));
		return false;
	}

	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Item ref invalid cannot fit inventory"));
		return false;
	}

	for (int x = Slot.X; x < Slot.X + Item->Size.X; x++)
	{
		if (x > Size.X) return false;

		for (int y = Slot.Y; y < Slot.Y + Item->Size.Y; y++)
		{
			if (y > Size.Y) return false;

			if (OccupiedSlots.Num() > 0 && OccupiedSlots.Contains(FIntPoint{ x,y })) return false;
		}
	}
	return true;
}

bool UInventoryComponent::SlotIsValid(FIntPoint Slot)
{
	return Slot.X > 0 && Slot.X <= Size.X && Slot.Y > 0 && Slot.Y <= Size.Y;
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

bool UInventoryComponent::TryAddItem(UItemDataAsset* DataAsset)
{
	TArray<FIntPoint> AvailableSlots = GetAvailableSlotsFor(DataAsset);

	if (AvailableSlots.Num() > 0)
	{
		FInventoryItem InventoryItem;
		InventoryItem.Item = DataAsset;
		InventoryItem.Position = AvailableSlots[0];
		Items.Add(InventoryItem);
		OnItemAdded.Broadcast(InventoryItem);
		return true;
	}

	return false;
}

