// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Stats/TimeStatUserWidget.h"
#include "Game/SurvivalScifiGameMode.h"
#include "Components/TextBlock.h"

void UTimeStatUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SurvivalScifiGameMode = Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode());

	if (SurvivalScifiGameMode == nullptr) UE_LOG(LogTemp, Error, TEXT("DateTime missing GameMode reference"));
}

void UTimeStatUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateDateTime();
}

void UTimeStatUserWidget::UpdateDateTime()
{
	if (SurvivalScifiGameMode != nullptr)
	{
		if (SurvivalScifiGameMode->GetDay() == 0)
		{
			Day->SetText(FText::FromString(""));
		}
		else
		{
			Day->SetText(FText::FromString("Sol " + FString::FromInt(SurvivalScifiGameMode->GetDay())));
		}
		
		Time->SetText(FText::FromString(FString::FromInt(SurvivalScifiGameMode->GetHour()) + ":00"));
	}
}
