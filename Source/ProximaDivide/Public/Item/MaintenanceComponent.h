// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MaintenanceComponent.generated.h"

USTRUCT(BlueprintType)
struct FRepairSlot
{
	GENERATED_BODY()

	// The item type that should go in this slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemDataAsset* RequiredItem = nullptr;

	// The item currently installed in the slot (can be nullptr)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemDataAsset* CurrentItem = nullptr;

	bool IsRepaired() { return RequiredItem == CurrentItem; }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UMaintenanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMaintenanceComponent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<FRepairSlot> RepairSlots;

	class APlayerCharacter* PlayerCharacter;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Total number of repair slots
	UFUNCTION()
	virtual int32 GetRepairSlotCount() const { return RepairSlots.Num(); }

	// Get all repair slots
	UFUNCTION()
	virtual const TArray<FRepairSlot>& GetRepairSlots() const { return RepairSlots; }

	// Optional: Check if fully repaired
	UFUNCTION()
	virtual bool IsFullyRepaired();

	UFUNCTION()
	virtual void AddItem(int32 SlotIndex, UItemDataAsset* Item);

	UFUNCTION()
	virtual void Repair(APlayerCharacter* playerCharacter);
		
};
