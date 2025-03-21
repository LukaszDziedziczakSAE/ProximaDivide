// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UInventoryUserWidget : public UUserWidget
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

public:
	UFUNCTION(BlueprintCallable)
	void SetInventory(UInventoryComponent* Inventory);
};
