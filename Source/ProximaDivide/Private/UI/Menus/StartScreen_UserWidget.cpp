// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Menus/StartScreen_UserWidget.h"
#include "Components/Button.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UStartScreen_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());

	StartButton->OnClicked.AddDynamic(this, &UStartScreen_UserWidget::OnStartButtonPress);
	ContinueButton->OnClicked.AddDynamic(this, &UStartScreen_UserWidget::OnContinueButtonPress);
	ExitButton->OnClicked.AddDynamic(this, &UStartScreen_UserWidget::OnExitButtonPress);

	if (GameInstance == nullptr)
	{
		ContinueButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		bool HasSaveGame = GameInstance->DoesSlotExist(0);
		ContinueButton->SetVisibility(HasSaveGame ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UStartScreen_UserWidget::OnStartButtonPress()
{
	if (GameInstance == nullptr) return;

	GameInstance->StartNewGame(0);
}

void UStartScreen_UserWidget::OnContinueButtonPress()
{
	if (GameInstance == nullptr) return;

	GameInstance->StartLoadGame(0);
}

void UStartScreen_UserWidget::OnExitButtonPress()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;

	if (World && PlayerController)
	{
		UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
	}
}
