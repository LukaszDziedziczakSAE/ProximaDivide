// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Components/OxygenComponent.h"
#include "Character/Player/PlayerCharacter.h"

void UOxygenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter == nullptr || !PlayerCharacter->bStatsLoaded) return;

	if (PlayerCharacter->bIsInside)
	{
		CurrentValue = FMath::Clamp(CurrentValue + (InsideModifyPerSecond * DeltaTime), 0, MaxValue);
	}
	else
	{
		CurrentValue = FMath::Clamp(CurrentValue + (OutsideModifyPerSecond * DeltaTime), 0, MaxValue);
	}
}
