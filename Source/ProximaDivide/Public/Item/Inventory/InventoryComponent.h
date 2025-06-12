// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/Inventory/FInventoryItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAddedSignature, FInventoryItem, InventoryItem);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInventoryItem> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIntPoint Size{ 1,1 };

	UFUNCTION()
	TArray<FIntPoint> Slots();

	UFUNCTION()
	TArray<FIntPoint> GetOccupiedSlots();

	UFUNCTION()
	TArray<FIntPoint> GetAvailableSlotsFor(class UItemDataAsset* DataAsset);

	UFUNCTION()
	bool ItemCanFitInSlot(FIntPoint Slot, UItemDataAsset* Item, TArray<FIntPoint> OccupiedSlots);

	UFUNCTION()
	bool SlotIsValid(FIntPoint Slot);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetItems(TArray<FInventoryItem> SavedItems) { Items = SavedItems; }

	UFUNCTION(BlueprintPure)
	TArray<FInventoryItem> GetItems() { return Items; }

	UFUNCTION(BlueprintPure)
	FIntPoint GetSize() { return Size; }

	UFUNCTION()
	bool TryAddItem(UItemDataAsset* DataAsset, bool bShowNotification = true);

	UFUNCTION()
	bool TryAddItemAt(UItemDataAsset* DataAsset, FIntPoint Position, bool isRotated = false);

	UFUNCTION()
	bool SlotIsOccupied(FIntPoint SlotCords);

	UPROPERTY(BlueprintAssignable)
	FOnItemAddedSignature OnItemAdded;

	UFUNCTION()
	bool CanAfford(class URecipeDataAsset* Recipe);

	UFUNCTION()
	bool HasItem(UItemDataAsset* DataAsset, int Amount = 1);

	UFUNCTION()
	bool TryRemoveItem(UItemDataAsset* DataAsset, int Amount = 1);

	UFUNCTION()
	bool TryRemoveItemAt(UItemDataAsset* DataAsset, FIntPoint Position);

	UFUNCTION()
	bool TakeItemsForRecipe(URecipeDataAsset* Recipe);

	UFUNCTION()
	bool AddItemsForRecipe(URecipeDataAsset* Recipe);

	UFUNCTION()
	bool CanAddItem(UItemDataAsset* DataAsset);
};
