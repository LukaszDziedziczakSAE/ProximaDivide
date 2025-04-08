// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/InventoryComponent.h"

#include "Item/ItemDataAsset.h"
#include "Item/RecipeDataAsset.h"
#include "Character/PlayerCharacter.h"
#include "UI/SurvivalScifi_HUD.h"


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

	for (int y = 1; y <= Size.Y; y++)
	{
		for (int x = 1; x <= Size.X; x++)
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

	for (int y = Slot.Y; y < Slot.Y + Item->Size.Y; y++)
	{
		if (y > Size.Y) return false;
	
		for (int x = Slot.X; x < Slot.X + Item->Size.X; x++)
		{
			if (x > Size.X) return false;

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

bool UInventoryComponent::TryAddItem(UItemDataAsset* DataAsset, bool bShowNotification)
{
	if (DataAsset == nullptr) return false;

	TArray<FIntPoint> AvailableSlots = GetAvailableSlotsFor(DataAsset);

	if (AvailableSlots.Num() > 0)
	{
		FInventoryItem InventoryItem;
		InventoryItem.Item = DataAsset;
		InventoryItem.Position = AvailableSlots[0];
		InventoryItem.Rotated = false;
		Items.Add(InventoryItem);
		UE_LOG(LogTemp, Log, TEXT("%s added to inventory at %s"), *InventoryItem.Item->Name, *InventoryItem.Position.ToString());
		if (bShowNotification) GetOwner<APlayerCharacter>()->GetHUD()->DisplayAddedItems(InventoryItem.Item);
		OnItemAdded.Broadcast(InventoryItem);
		return true;
	}

	return false;
}

bool UInventoryComponent::TryAddItemAt(UItemDataAsset* DataAsset, FIntPoint Position, bool isRotated)
{
	if (DataAsset == nullptr) return false;

	TArray<FIntPoint> AvailableSlots = GetAvailableSlotsFor(DataAsset);

	if (AvailableSlots.Contains(Position))
	{
		FInventoryItem InventoryItem;
		InventoryItem.Item = DataAsset;
		InventoryItem.Position = Position;
		InventoryItem.Rotated = isRotated;
		Items.Add(InventoryItem);
		UE_LOG(LogTemp, Log, TEXT("%s added to inventory at %s"), *InventoryItem.Item->Name, *InventoryItem.Position.ToString());
		OnItemAdded.Broadcast(InventoryItem);
		return true;
	}

	return false;
}

bool UInventoryComponent::SlotIsOccupied(FIntPoint SlotCords)
{
	return GetOccupiedSlots().Contains(SlotCords);
}

bool UInventoryComponent::CanAfford(URecipeDataAsset* Recipe)
{
	for (FRecipeItem RecipieItem : Recipe->RecipeItems)
	{
		if (!HasItem(RecipieItem.Item, RecipieItem.Amount))
			return false;
	}
		

	return true;
}

bool UInventoryComponent::HasItem(UItemDataAsset* DataAsset, int Amount)
{
	int count = 0;

	for (FInventoryItem InventoryItem : Items)
		if (InventoryItem.Item == DataAsset) count++;

	UE_LOG(LogTemp, Log, TEXT("Have %d %s, need %d"), count, *DataAsset->Name, Amount);
	return count >= Amount;
}

bool UInventoryComponent::TryRemoveItem(UItemDataAsset* DataAsset, int Amount)
{
	if (HasItem(DataAsset, Amount))
	{
		TArray<FInventoryItem> ItemsToRemove;

		for (FInventoryItem InventoryItem : Items)
		{
			if (InventoryItem.Item == DataAsset &&
				ItemsToRemove.Num() < Amount)
				ItemsToRemove.Add(InventoryItem);
	}
			

		for (FInventoryItem InventoryItem : ItemsToRemove)
			Items.Remove(InventoryItem);

		return true;
	}

	return false;
}

bool UInventoryComponent::TryRemoveItemAt(UItemDataAsset* DataAsset, FIntPoint Position)
{
	FInventoryItem ItemToRemove;
	for (FInventoryItem InventoryItem : Items)
	{
		if (InventoryItem.Item == DataAsset, InventoryItem.Position == Position)
		{
			ItemToRemove = InventoryItem;
		}
	}
	if (ItemToRemove.Item != nullptr)
	{
		Items.Remove(ItemToRemove);
		return true;
	}
	return false;
}

bool UInventoryComponent::TakeItemsForRecipe(URecipeDataAsset* Recipe)
{
	for (FRecipeItem RecipieItem : Recipe->RecipeItems)
	{
		if (!TryRemoveItem(RecipieItem.Item, RecipieItem.Amount))
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to take %d %s from inventory"), RecipieItem.Amount, *RecipieItem.Item->Name);
			return false;
		}
		else
		{
			GetOwner<APlayerCharacter>()->GetHUD()->DisplayRemovedItems(RecipieItem.Item, RecipieItem.Amount);
		}
	}
		
	return true;
}

bool UInventoryComponent::AddItemsForRecipe(URecipeDataAsset* Recipe)
{
	if (Recipe == nullptr) return false;

	if (TryAddItem(Recipe->Item))
	{
		return true;
	}
	return false;
}

bool UInventoryComponent::CanAddItem(UItemDataAsset* DataAsset)
{
	TArray<FIntPoint> OccupiedSlots = GetOccupiedSlots();

	for (FIntPoint Slot : Slots())
	{
		if (ItemCanFitInSlot(Slot, DataAsset, OccupiedSlots))
			return true;
	}

	return false;
}

