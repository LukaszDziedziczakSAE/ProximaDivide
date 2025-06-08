// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Misc/CurrentSaveInfo_UserWidget.h"
#include "Components/TextBlock.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "Game/SurvivalScifi_SaveGame.h"

void UCurrentSaveInfo_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
	if (GameInstance != nullptr && GameInstance->GetCurrentSaveGame() != nullptr)
	{
		SlotNumberText->SetText(FText::FromString(TEXT("Slot ") + FString::FromInt(GameInstance->GetCurrentSaveGame()->SlotNumber)));

		CurrentLevelNameText->SetText(FText::FromName(GameInstance->GetCurrentSaveGame()->CurrentLevelName));

		PlayerStartTagText->SetText(FText::FromName(GameInstance->GetCurrentSaveGame()->PlayerStartTag));

		EnviromentText->SetText(StaticEnum<EEnviroment>()->GetDisplayNameTextByValue((int64)GameInstance->GetCurrentSaveGame()->Enviroment));

	}
	else
	{
		SlotNumberText->SetText(FText::FromString("No Save Data"));

		CurrentLevelNameText->SetText(FText::FromString(""));

		PlayerStartTagText->SetText(FText::FromString(""));

		EnviromentText->SetText(FText::FromString(""));
	}
}
