// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/Crafting/ItemDataAsset.h"

inline bool UItemDataAsset::operator==(const UItemDataAsset& ItemDataAsset)
{
    return Name.Equals(ItemDataAsset.Name);
}
