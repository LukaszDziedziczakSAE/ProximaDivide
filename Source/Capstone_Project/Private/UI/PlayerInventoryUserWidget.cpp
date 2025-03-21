// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PlayerInventoryUserWidget.h"
#include "UI/InventoryUserWidget.h"
#include "Character/PlayerCharacter.h"

void UPlayerInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Constructing Player Inventory Widget"));

	InventoryWidget->SetInventory(PlayerCharacter->GetInventoryComponent());
}
