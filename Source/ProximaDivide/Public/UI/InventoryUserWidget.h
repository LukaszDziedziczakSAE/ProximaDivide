// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeDestruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CellSize{ 100.0f };

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* InventoryOverlay;

	//UPROPERTY(meta = (BindWidget))
	//class UUniformGridPanel* Grid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UInventorySlotUserWidget> SlotClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UInventoryItemUserWidget> ItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UInventorySlotUserWidget*> Slots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UInventoryItemUserWidget*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerInventoryUserWidget* PlayerInventoryUserWidget;

public:
	UFUNCTION(BlueprintCallable)
	void SetInventory(UInventoryComponent* Inventory, UPlayerInventoryUserWidget* Widget);

	UFUNCTION(BlueprintCallable)
	void RefreshSlots();

	UFUNCTION(BlueprintCallable)
	void ClearSlots();

	UFUNCTION()
	TArray<UInventorySlotUserWidget*> GetSlots(){ return Slots; }

	UFUNCTION()
	void ResetSlotsToOccupancy();

	UFUNCTION()
	void ShowAvailability(class UItemDataAsset* Item, FIntPoint Position);

	UFUNCTION()
	UInventoryComponent* GetInventory() { return InventoryComponent; }
};
