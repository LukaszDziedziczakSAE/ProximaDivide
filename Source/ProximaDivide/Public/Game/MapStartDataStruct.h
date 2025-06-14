// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "MapStartDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FMapStartData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName MapName;

	UPROPERTY(EditAnywhere)
	FName PlayerStartTag;

	FMapStartData()
	{
		MapName = FName();
		PlayerStartTag = FName();
	}

	FMapStartData(FName mapName, FName playerStartTag)
	{
		MapName = mapName;
		PlayerStartTag = playerStartTag;
	}

	bool operator==(const FMapStartData& Other) const
	{
		return MapName == Other.MapName && PlayerStartTag == Other.PlayerStartTag;
	}

};

FORCEINLINE uint32 GetTypeHash(const FMapStartData& Data)
{
	uint32 Hash = GetTypeHash(Data.MapName);
	Hash = HashCombine(Hash, GetTypeHash(Data.PlayerStartTag));
	return Hash;
}
