// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "DragUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UDragUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CellSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Rotated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemDataAsset* Item;

	UFUNCTION()
	USizeBox* GetSizeBox() { return SizeBox; }
};
