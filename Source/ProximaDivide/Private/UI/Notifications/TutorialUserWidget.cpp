// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Notifications/TutorialUserWidget.h"
#include "Components/SizeBox.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerTutorialComponent.h"

UTutorialUserWidget::UTutorialUserWidget()
{
}

void UTutorialUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateTutorialInfo();
}

void UTutorialUserWidget::UpdateTutorialInfo()
{
	MouseLookInfo->SetVisibility(
		PlayerCharacter->GetTutorialComponent()->ShowMouseMoveInfo 
		? ESlateVisibility::HitTestInvisible 
		: ESlateVisibility::Collapsed);

	MovementInfo->SetVisibility(
		PlayerCharacter->GetTutorialComponent()->ShowMovementInfo
		? ESlateVisibility::HitTestInvisible
		: ESlateVisibility::Collapsed);

	JumpInfo->SetVisibility(
		PlayerCharacter->GetTutorialComponent()->ShowJumpInfo
		? ESlateVisibility::HitTestInvisible
		: ESlateVisibility::Collapsed);

	InventoryInfo->SetVisibility(
		PlayerCharacter->GetTutorialComponent()->ShowInventoryInfo
		? ESlateVisibility::HitTestInvisible
		: ESlateVisibility::Collapsed);

	SlotInfo->SetVisibility(
		PlayerCharacter->GetTutorialComponent()->ShowSlotInfo
		? ESlateVisibility::HitTestInvisible
		: ESlateVisibility::Collapsed);
}
