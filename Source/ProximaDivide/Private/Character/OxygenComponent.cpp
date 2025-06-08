// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/OxygenComponent.h"
#include "Character/PlayerCharacter.h"

void UOxygenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter->bIsInside)
	{
		CurrentValue = FMath::Clamp(CurrentValue + (InsideModifyPerSecond * DeltaTime), 0, MaxValue);
	}
	else
	{
		CurrentValue = FMath::Clamp(CurrentValue + (OutsideModifyPerSecond * DeltaTime), 0, MaxValue);
	}
}
