// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/PlayerStatsUserWidget.h"
#include "UI/StatUserWidget.h"
#include "Character/PlayerCharacter.h"
#include "Character/StatComponent.h"

void UPlayerStatsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OxygenStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetOxygenComponent());
	HealthStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetHealthComponent());
	SustenanceStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetSustenanceComponent());
	ExhaustionStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetExhaustionComponent());
}
