// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SurvivalScifi_DragDropOperation.generated.h"

UCLASS()
class PROXIMADIVIDE_API USurvivalScifi_DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDragUserWidget* DragUserWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CellSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Rotated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D DragOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint ToInventoryPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint FromInventoryPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemDataAsset* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* FromInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* ToInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ToSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int FromSlot;
};
