// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "PaperdollSlotUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UPaperdollSlotUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	int SlotNumber;

	UPROPERTY(meta = (BindWidget))
	class UImage* SelectionIndicator;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UDragUserWidget> DragUserWidgetClass;

	UFUNCTION()
	struct FSlotItem PaperdollSlot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CellSize{ 100.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor SelectedColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor UnselectedColor;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateSlot();
};
