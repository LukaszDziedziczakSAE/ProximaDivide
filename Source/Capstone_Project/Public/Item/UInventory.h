// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UInventory.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class UGameItem*> Items;
	
};
