// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/GameplayHUD/SurvivalScifi_START_HUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void ASurvivalScifi_START_HUD::BeginPlay()
{
	Super::BeginPlay();

	StartScreen->AddToViewport();
	
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerControllerRef->SetShowMouseCursor(true);
	PlayerControllerRef->SetInputMode(FInputModeUIOnly());
}
