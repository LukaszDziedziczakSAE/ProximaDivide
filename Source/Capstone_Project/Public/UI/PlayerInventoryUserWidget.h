// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "PlayerInventoryUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UPlayerInventoryUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY( meta = (BindWidget))
	class UInventoryUserWidget* InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	class UPaperdollSlotUserWidget* PaperdollSlot1;
	
	UPROPERTY(meta = (BindWidget))
	class UPaperdollSlotUserWidget* PaperdollSlot2;

	UPROPERTY(meta = (BindWidget))
	class UPaperdollSlotUserWidget* PaperdollSlot3;

	UPROPERTY(meta = (BindWidget))
	class UPaperdollSlotUserWidget* PaperdollSlot4;

	UPROPERTY(meta = (BindWidget))
	class UPaperdollSlotUserWidget* PaperdollSlot5;
};
