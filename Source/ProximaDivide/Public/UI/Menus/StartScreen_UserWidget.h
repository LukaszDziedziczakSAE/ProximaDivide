// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "StartScreen_UserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UStartScreen_UserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY()
	class USurvivalSciFi_GameInstance* GameInstance;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SkipIntroButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UFUNCTION()
	void OnStartButtonPress();

	UFUNCTION()
	void OnContinueButtonPress();

	UFUNCTION()
	void OnExitButtonPress();

	UFUNCTION()
	void OnSkipIntroButtonPress();
};
