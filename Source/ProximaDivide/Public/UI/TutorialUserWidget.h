// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "TutorialUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UTutorialUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

public:
	UTutorialUserWidget();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* MouseLookInfo;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* MovementInfo;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* JumpInfo;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* InventoryInfo;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SlotInfo;

public:
	UFUNCTION()
	void UpdateTutorialInfo();
};
