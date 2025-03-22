// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "PaperdollSlotUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UPaperdollSlotUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	int SlotNumber;

	UPROPERTY(meta = (BindWidget))
	class UImage* SelectionIndicator;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

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
