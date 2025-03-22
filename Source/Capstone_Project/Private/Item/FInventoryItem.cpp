#include "Item\FInventoryItem.h"
#include "Item\ItemDataAsset.h"

TArray<FIntPoint> FInventoryItem::OccupiedSlots()
{
    TArray<FIntPoint> OccupiedSlots;

    for (int x = Position.X; x < Position.X + Item->Size.X; x++)
    {
        for (int y = Position.Y; y < Position.Y + Item->Size.Y; y++)
        {
            OccupiedSlots.Add(FIntPoint{ x,y });
        }
    }

    return OccupiedSlots;
}

TArray<FIntPoint> FInventoryItem::OccupiedSlotsRotated()
{
    TArray<FIntPoint> OccupiedSlots;

    for (int x = Position.X; x < Position.X + Item->Size.Y; x++)
    {
        for (int y = Position.Y; y < Position.Y + Item->Size.X; y++)
        {
            OccupiedSlots.Add(FIntPoint{ x,y });
        }
    }

    return OccupiedSlots;
}
