// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NoItemType UMETA(DisplayName = "No Item Type"),
	RawMaterial UMETA(DisplayName = "Raw Material"),
	RefinedMaterial UMETA(DisplayName = "Refined Material"),
	Component UMETA(DisplayName = "Component"),
	Junk UMETA(DisplayName = "Junk"),
	Tool UMETA(DisplayName = "Tool"),
	Weapon UMETA(DisplayName = "Weapon"),
	Consumable UMETA(DisplayName = "Consumable")
};

UCLASS()
class PROXIMADIVIDE_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ASurvivalScifi_Item> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ImageRotated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIntPoint Size{ 1,1 };

	UFUNCTION(BlueprintPure)
	bool bCanRotate() { return Size.X != Size.Y; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class URecipeDataAsset* LearnOnDiscovery;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UScrapDataAsset* ScrapData;

	inline bool operator==(const UItemDataAsset& ItemDataAsset);
};
