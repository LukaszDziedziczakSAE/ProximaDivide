// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/TittleCard_UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTittleCard_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetGameNameAlpha(0);
	SetCreatedByAlpha(0);
	SetBackgroundAlpha(0);
	TitleCardState = ETitleCardState::InitialPause;
	Timer = 0;
}

void UTittleCard_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Timer += InDeltaTime;

    switch (TitleCardState)
    {
    case ETitleCardState::InitialPause:
        if (Timer >= InitialPauseTime)
        {
            Timer = 0;
            TitleCardState = ETitleCardState::GameNameFadeIn;
        }
        break;

    case ETitleCardState::GameNameFadeIn:
        if (Timer >= GameNameFadeInTime)
        {
            SetGameNameAlpha(1.0f);
            Timer = 0;
            TitleCardState = ETitleCardState::GameNameDisplay;
        }
        else
        {
            SetGameNameAlpha(FMath::Lerp(0.0f, 1.0f, Timer / GameNameFadeInTime));
        }
        break;

    case ETitleCardState::GameNameDisplay:
        if (Timer >= GameNameTime)
        {
            Timer = 0;
            TitleCardState = ETitleCardState::GameNameFadeOut;
        }
        break;

    case ETitleCardState::GameNameFadeOut:
        if (Timer >= GameNameFadeOutTime)
        {
            SetGameNameAlpha(0.0f);
            Timer = 0;
            TitleCardState = ETitleCardState::PauseBetweenCards;
        }
        else
        {
            SetGameNameAlpha(FMath::Lerp(1.0f, 0.0f, Timer / GameNameFadeOutTime));
        }
        break;

    case ETitleCardState::PauseBetweenCards:
        if (Timer >= PauseBetweenCards)
        {
            Timer = 0;
            TitleCardState = ETitleCardState::CreatedByFadeIn;
        }
        break;

    case ETitleCardState::CreatedByFadeIn:
        if (Timer >= CreatedByFadeInTime)
        {
            SetCreatedByAlpha(1.0f);
            Timer = 0;
            TitleCardState = ETitleCardState::CreatedByDisplay;
        }
        else
        {
            SetCreatedByAlpha(FMath::Lerp(0.0f, 1.0f, Timer / CreatedByFadeInTime));
        }
        break;

    case ETitleCardState::CreatedByDisplay:
        if (Timer >= CreatedByTime)
        {
            Timer = 0;
            TitleCardState = ETitleCardState::CreatedByFadeOut;
        }
        break;

    case ETitleCardState::CreatedByFadeOut:
        if (Timer >= CreatedByFadeOutTime)
        {
            SetCreatedByAlpha(0.0f);
            Timer = 0;
            TitleCardState = ETitleCardState::BackgroundFadeIn;
        }
        else
        {
            SetCreatedByAlpha(FMath::Lerp(1.0f, 0.0f, Timer / CreatedByFadeOutTime));
        }
        break;

    case ETitleCardState::BackgroundFadeIn:
        if (Timer >= BackgroundFadeInTime)
        {
            SetBackgroundAlpha(1.0f);
            Timer = 0;
            TitleCardState = ETitleCardState::Finished;
        }
        else
        {
            SetBackgroundAlpha(FMath::Lerp(0.0f, 1.0f, Timer / BackgroundFadeInTime));
        }
        break;
    }

}

void UTittleCard_UserWidget::SetGameNameAlpha(float Alpha)
{
    if (!GameName) return;

	GameName->SetRenderOpacity(FMath::Clamp(Alpha, 0.0f, 1.0f));
}

void UTittleCard_UserWidget::SetCreatedByAlpha(float Alpha)
{
	if (!CreatedBy) return;

	CreatedBy->SetRenderOpacity(FMath::Clamp(Alpha, 0.0f, 1.0f));
}

void UTittleCard_UserWidget::SetBackgroundAlpha(float Alpha)
{
	FLinearColor BackgroundColor =  Background->ColorAndOpacity;
	BackgroundColor.A = Alpha;
	Background->SetColorAndOpacity(BackgroundColor);
}
