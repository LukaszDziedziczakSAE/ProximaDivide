// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

UCLASS()
class PROXIMADIVIDE_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

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

	inline bool operator==(const UItemDataAsset& ItemDataAsset);
};
