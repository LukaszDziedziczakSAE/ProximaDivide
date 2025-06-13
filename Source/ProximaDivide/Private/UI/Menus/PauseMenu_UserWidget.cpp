// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Menus/PauseMenu_UserWidget.h"
#include "Components/Button.h"
#include "Game/SurvivalScifi_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SurvivalSciFi_GameInstance.h"

void UPauseMenu_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnResumeButtonPress);
	SaveButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnSaveButtonPress);
	LoadButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnLoadButtonPress);
	SettingsButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnSettingsButtonPress);
	ReturnToStartButton->OnClicked.AddDynamic(this, &UPauseMenu_UserWidget::OnReturnToStartButtonPress);

	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
}

void UPauseMenu_UserWidget::OnResumeButtonPress()
{
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();
}

void UPauseMenu_UserWidget::OnSaveButtonPress()
{
	if (GameInstance != nullptr)
	{
		GameInstance->SaveCurrentGame();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is null in UPauseMenu_UserWidget::OnSaveButtonPress"));
		return;
	}


	//Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode())->SaveGame();
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();
}

void UPauseMenu_UserWidget::OnLoadButtonPress()
{
	GetOwningPlayer<ASurvivalScifi_PlayerController>()->PauseToggle();

	if (GameInstance != nullptr)
	{
		GameInstance->StartLoadGame(0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is null in UPauseMenu_UserWidget::OnLoadButtonPress"));
		return;
	}
	//Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode())->LoadGame(0);
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
