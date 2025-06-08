// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Menus/PauseMenu_UserWidget.h"
#include "Components/Button.h"
#include "Game/SurvivalScifi_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SurvivalScifiGameMode.h"

void UPauseMenu_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnResumeButtonPress);
	SaveButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnSaveButtonPress);
	LoadButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnLoadButtonPress);
	SettingsButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnSettingsButtonPress);
	ReturnToStartButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnReturnToStartButtonPress);
}

void UPauseMenu_UserWidget::OnResumeButtonPress()
{
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();
}

void UPauseMenu_UserWidget::OnSaveButtonPress()
{
	Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode())->SaveGame();
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();
}

void UPauseMenu_UserWidget::OnLoadButtonPress()
{
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();
	Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode())->LoadGame(0);
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
