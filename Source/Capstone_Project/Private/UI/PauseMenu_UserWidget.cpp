// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PauseMenu_UserWidget.h"
#include "Components/Button.h"
#include "Game/SurvivalScifi_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu_UserWidget::NativeConstruct()
{
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnResumeButtonPress);
	SettingsButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnSettingsButtonPress);
	ReturnToStartButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnReturnToStartButtonPress);
}

void UPauseMenu_UserWidget::OnResumeButtonPress()
{
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();
}

void UPauseMenu_UserWidget::OnSettingsButtonPress()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, TEXT("Settings menu not implemented yet"));
}

void UPauseMenu_UserWidget::OnReturnToStartButtonPress()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_Start"));
}
