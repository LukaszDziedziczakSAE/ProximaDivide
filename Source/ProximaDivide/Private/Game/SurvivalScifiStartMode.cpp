// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalScifiStartMode.h"
#include "Game/SurvivalSciFi_GameInstance.h"

void ASurvivalScifiStartMode::BeginPlay()
{
	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
	if (GameInstance != nullptr)
	{
		GameInstance->SetEnviroment(EEnviroment::Menu);
		GameInstance->PlayMusicAndAmbience();
	}
}
