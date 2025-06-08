// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Stats/PlayerStatsUserWidget.h"
#include "UI/Stats/StatUserWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Components/StatComponent.h"
#include "Character/Components/OxygenComponent.h"
#include "Character/Components/HealthComponent.h"
#include "Character/Components/SustenanceComponent.h"
#include "Character/Components/ExhaustionComponent.h"

void UPlayerStatsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OxygenStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetOxygenComponent());
	HealthStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetHealthComponent());
	SustenanceStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetSustenanceComponent());
	ExhaustionStat->StatComponent = Cast<UStatComponent>(PlayerCharacter->GetExhaustionComponent());
}
