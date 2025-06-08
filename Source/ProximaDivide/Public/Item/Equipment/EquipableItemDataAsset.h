// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/Crafting/ItemDataAsset.h"
#include "Character/EAnimHandsType.h"
#include "EquipableItemDataAsset.generated.h"

UCLASS()
class PROXIMADIVIDE_API UEquipableItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAnimHandsType AnimHandsType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ASurvivalScifi_Item> RightHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ASurvivalScifi_Item> LeftHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* UseageMontage;
};
