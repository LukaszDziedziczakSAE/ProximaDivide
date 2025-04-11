// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemDataAsset.h"
#include "SingleUseItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API USingleUseItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ASurvivalScifi_Item> RightHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ASurvivalScifi_Item> LeftHand;
};
