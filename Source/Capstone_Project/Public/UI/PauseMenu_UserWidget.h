// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "PauseMenu_UserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UPauseMenu_UserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ReturnToStartButton;

	UFUNCTION()
	void OnResumeButtonPress();

	UFUNCTION()
	void OnSettingsButtonPress();

	UFUNCTION()
	void OnReturnToStartButtonPress();
	
};
