// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/EAnimHandsType.h"
#include "PaperdollComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotChangeSignature);

USTRUCT(BlueprintType)
struct FSlotItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UEquipableItemDataAsset* Item;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UPaperdollComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPaperdollComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSlotChangeSignature OnSlotChange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Index{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlotItem Slot1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlotItem Slot2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlotItem Slot3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlotItem Slot4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlotItem Slot5;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool TryAddEquipable(UEquipableItemDataAsset* Equipable);

	UFUNCTION(BlueprintCallable)
	bool TryAddEquipableToSlot(UEquipableItemDataAsset* Equipable, int SlotNumber);

	UFUNCTION(BlueprintCallable)
	bool TryRemoveItemFromSlot(int SlotNumber);

	UFUNCTION(BlueprintPure)
	int GetCurrentSlotNumber() { return Index; }

	UFUNCTION(BlueprintCallable)
	FSlotItem GetSlot(int SlotNumber);

	UFUNCTION(BlueprintCallable)
	FSlotItem GetCurrentSlot();

	UFUNCTION(BlueprintPure)
	EAnimHandsType GetCurrentAnimHandsType();

	UFUNCTION(BlueprintPure)
	FSlotItem GetSlot1() { return Slot1; }

	UFUNCTION(BlueprintPure)
	FSlotItem GetSlot2() { return Slot2; }

	UFUNCTION(BlueprintPure)
	FSlotItem GetSlot3() { return Slot3; }

	UFUNCTION(BlueprintPure)
	FSlotItem GetSlot4() { return Slot4; }

	UFUNCTION(BlueprintPure)
	FSlotItem GetSlot5() { return Slot5; }

	UFUNCTION()
	void SelectSlot(int SlotNumber);

	UFUNCTION()
	bool DoesSlotHaveItem(int SlotNumber);

	UFUNCTION(BlueprintPure)
	bool IsCurrentSlotHaveItem();

	UFUNCTION()
	void CurrentSlotSingleUseItem();
};
