// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/HealthComponent.h"
#include "Character/OxygenComponent.h"
#include "Character/SustenanceComponent.h"
#include "Character/ExhaustionComponent.h"
#include "Character/PlayerCharacter.h"


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter != nullptr)
	{
		if (PlayerCharacter->GetOxygenComponent()->GetCurrentValue() <= 0
			|| PlayerCharacter->GetSustenanceComponent()->GetCurrentValue() <= 0
			|| PlayerCharacter->GetExhaustionComponent()->GetCurrentValue() <= 0)
		{
			CurrentValue = FMath::Clamp(CurrentValue + (ZeroStatHealthLoss * DeltaTime), 0, MaxValue);
		}
	}
}

