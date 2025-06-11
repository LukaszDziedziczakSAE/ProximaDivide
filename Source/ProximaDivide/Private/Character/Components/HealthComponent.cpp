// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Components/HealthComponent.h"
#include "Character/Components/OxygenComponent.h"
#include "Character/Components/SustenanceComponent.h"
#include "Character/Components/ExhaustionComponent.h"
#include "Character/Player/PlayerCharacter.h"


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter == nullptr || !PlayerCharacter->bStatsLoaded || PlayerCharacter->IsPlayingSequence()) return;
	
	if (PlayerCharacter->GetOxygenComponent()->GetCurrentValue() <= 0
		|| PlayerCharacter->GetSustenanceComponent()->GetCurrentValue() <= 0
		|| PlayerCharacter->GetExhaustionComponent()->GetCurrentValue() >= PlayerCharacter->GetExhaustionComponent()->GetMaxValue())
	{
		CurrentValue = FMath::Clamp(CurrentValue + (ZeroStatHealthLoss * DeltaTime), 0, MaxValue);
	}
}

