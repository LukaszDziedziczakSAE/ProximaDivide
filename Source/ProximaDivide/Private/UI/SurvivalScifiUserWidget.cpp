// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/SurvivalScifiUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter.h"

void USurvivalScifiUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
