// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/ItemDataAsset.h"

inline bool UItemDataAsset::operator==(const UItemDataAsset& ItemDataAsset)
{
    return Name.Equals(ItemDataAsset.Name);
}
