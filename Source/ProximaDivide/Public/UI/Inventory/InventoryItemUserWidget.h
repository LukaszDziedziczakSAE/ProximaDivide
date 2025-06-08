// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "InventoryItemUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UInventoryItemUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UDragUserWidget> DragUserWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemDataAsset* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CellSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bRotated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint Position;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SlotNumber;

	UFUNCTION()
	void Orient();

	UFUNCTION()
	void UpdateImage();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerInventoryUserWidget* PlayerInventoryUserWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASurvivalScifi_HUD* HUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* Inventory;

public:
	UFUNCTION()
	void Set(UInventoryComponent* FromInventory, UItemDataAsset* ItemData, float NewCellSize, FIntPoint NewPosition = FIntPoint(0, 0), bool Rotated = false, int NewSlotNumber = 0);

	UFUNCTION()
	void Rotate();

	UFUNCTION(BlueprintPure)
	UItemDataAsset* GetItem() { return Item; }

	UFUNCTION(BlueprintPure)
	FIntPoint GetPosition(){ return Position; }

	UFUNCTION(BlueprintPure)
	int GetSlotNumber() { return SlotNumber; }

	UFUNCTION(BlueprintPure)
	float GetCellSize() { return CellSize; }

	UFUNCTION()
	UInventoryComponent* GetInventory() { return Inventory; }
};
