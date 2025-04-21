// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "TimeStatUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API UTimeStatUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	class ASurvivalScifiGameMode* SurvivalScifiGameMode;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Day;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Time;

public:

	UFUNCTION()
	void UpdateDateTime();
	
};
