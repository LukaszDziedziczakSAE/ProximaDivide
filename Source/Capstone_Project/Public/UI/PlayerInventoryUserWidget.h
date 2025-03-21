// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "PlayerInventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API UPlayerInventoryUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY( meta = (BindWidget))
	class UInventoryUserWidget* InventoryWidget;
	
};
