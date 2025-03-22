// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<struct FInventoryItem> Items;

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	FIntPoint GetSize() { return Size; }

	UFUNCTION()
	TArray<struct FInventoryItem> GetItems() { return Items; }

	UFUNCTION()
	bool TryAddItem(UItemDataAsset* DataAsset);
};
