// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameItem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API UGameItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint Location; // in inventory. 0,0 if not in inventory

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Rotated;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTexture* Icon;*/
};
