// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TittleCard_UserWidget.generated.h"

UENUM(BlueprintType)
enum class ETitleCardState : uint8
{
	InitialPause       UMETA(DisplayName = "Initial Pause"),
	GameNameFadeIn     UMETA(DisplayName = "Game Name Fade In"),
	GameNameDisplay    UMETA(DisplayName = "Game Name Display Time"),
	GameNameFadeOut    UMETA(DisplayName = "Game Name Fade Out"),
	PauseBetweenCards  UMETA(DisplayName = "Pause Between Cards"),
	CreatedByFadeIn    UMETA(DisplayName = "Created By Fade In"),
	CreatedByDisplay   UMETA(DisplayName = "Created By Display Time"),
	CreatedByFadeOut   UMETA(DisplayName = "Created By Fade Out"),
	BackgroundFadeIn   UMETA(DisplayName = "Background Fade In"),
	Finished           UMETA(DisplayName = "Finished")
};

UCLASS()
class CAPSTONE_PROJECT_API UTittleCard_UserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UImage* Background;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CreatedBy;
	
	UPROPERTY()
	float Timer;

	UPROPERTY(EditDefaultsOnly)
	float InitialPauseTime = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float GameNameFadeInTime = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float GameNameTime = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	float GameNameFadeOutTime = 0.8f;

	UPROPERTY(EditDefaultsOnly)
	float PauseBetweenCards = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CreatedByFadeInTime = 0.8f;

	UPROPERTY(EditDefaultsOnly)
	float CreatedByTime = 1.2f;

	UPROPERTY(EditDefaultsOnly)
	float CreatedByFadeOutTime = 0.8f;

	UPROPERTY(EditDefaultsOnly)
	float BackgroundFadeInTime = 0.8f;

	UPROPERTY(VisibleAnywhere)
	ETitleCardState TitleCardState;

	UFUNCTION()
	void SetGameNameAlpha(float Alpha);

	UFUNCTION()
	void SetCreatedByAlpha(float Alpha);

	UFUNCTION()
	void SetBackgroundAlpha(float Alpha);
};
