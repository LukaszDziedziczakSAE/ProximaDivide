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

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASurvivalScifi_HUD* HUD;

	
public:
	UFUNCTION(BlueprintPure)
	FIntPoint GetPosition() { return Position; }

	UFUNCTION()
	void SetPosition(FIntPoint NewPosition);

	UFUNCTION()
	void SetSize(float Size);

	UFUNCTION()
	void SetOccupied(bool bIsOccupied);
};
