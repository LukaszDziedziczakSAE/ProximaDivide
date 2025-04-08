// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UInventorySlotUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(meta = (BindWidget))
	class UImage* CellImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Cords;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint Position;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor FreeColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor OccupiedColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor CanDropColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor CannotDropColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASurvivalScifi_HUD* HUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D PositionInViewport;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isOccupied;

	
public:
	UFUNCTION(BlueprintPure)
	FIntPoint GetPosition() { return Position; }

	UFUNCTION()
	void SetPosition(FIntPoint NewPosition);

	UFUNCTION()
	void SetSize(float Size);

	UFUNCTION()
	void SetOccupied(bool bIsOccupied);

	UFUNCTION()
	void ResetToOccupied();

	UFUNCTION()
	void ShowCanDropTo();

	UFUNCTION()
	FVector2D GetPositionInViewport() { return PositionInViewport; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerInventoryUserWidget* PlayerInventoryUserWidget;
};
