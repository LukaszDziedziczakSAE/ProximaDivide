// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/FInventoryItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAddedSignature, FInventoryItem, InventoryItem);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UInventoryComponent : public UActorComponent
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
	FIntPoint GetSize() { return Size; }

	UFUNCTION()
	TArray<struct FInventoryItem> GetItems() { return Items; }

	UFUNCTION()
	bool TryAddItem(UItemDataAsset* DataAsset);

	UPROPERTY(BlueprintAssignable)
	FOnItemAddedSignature OnItemAdded;
};
