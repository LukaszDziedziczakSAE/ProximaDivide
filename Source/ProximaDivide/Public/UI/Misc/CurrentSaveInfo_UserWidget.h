// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "CurrentSaveInfo_UserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UCurrentSaveInfo_UserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY()
	class USurvivalSciFi_GameInstance* GameInstance;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SlotNumberText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentLevelNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerStartTagText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnviromentText;
};
