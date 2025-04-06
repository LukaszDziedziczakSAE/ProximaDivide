// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "InventoryItemUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UInventoryItemUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

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

public:
	UFUNCTION()
	void Set(UItemDataAsset* ItemData, float NewCellSize, bool Rotated = false, FIntPoint NewPosition = FIntPoint(0,0), int NewSlotNumber = 0);

	UFUNCTION()
	void Rotate();

	UFUNCTION(BlueprintPure)
	UItemDataAsset* GetItem() { return Item; }

	UFUNCTION(BlueprintPure)
	FIntPoint GetPosition(){ return Position; }

	UFUNCTION(BlueprintPure)
	int GetSlotNumber() { return SlotNumber; }

	UFUNCTION(BlueprintCallable)
	void OnMouseDown();
};
