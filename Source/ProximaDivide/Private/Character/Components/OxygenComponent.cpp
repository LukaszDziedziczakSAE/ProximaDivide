// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Components/OxygenComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerSuitVoiceComponent.h"

void UOxygenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter == nullptr || !PlayerCharacter->bStatsLoaded || PlayerCharacter->IsPlayingSequence()) return;

	if (PlayerCharacter->bIsInside)
	{
		CurrentValue = FMath::Clamp(CurrentValue + (InsideModifyPerSecond * DeltaTime), 0, MaxValue);
	}
	else
	{
		CurrentValue = FMath::Clamp(CurrentValue + (OutsideModifyPerSecond * DeltaTime), 0, MaxValue);
	}

	// Low oxygen warning
	if (bOxygenLowGiven)
	{
		if (CurrentValue >= LowOxygenThreshold)
			bOxygenLowGiven = false;
	}
	else
	{
		if (CurrentValue < LowOxygenThreshold)
		{
			PlayerCharacter->GetSuitVoiceComponent()->Play(OxygenLow);
			bOxygenLowGiven = true;
		}
	}

	// 50% oxygen warning
	if (bOxygen50pGiven)
	{
		if (GetPercentage() >= 0.51f)
			bOxygen50pGiven = false;
	}
	else
	{
		if (GetPercentage() < 0.51f)
		{
			PlayerCharacter->GetSuitVoiceComponent()->Play(Oxygen50p);
			bOxygen50pGiven = true;
		}
	}

	// 30 seconds left warning
	if (bOxygen30sGiven)
	{
		if (CurrentValue >= 31.0f)
			bOxygen30sGiven = false;
	}
	else
	{
		if (CurrentValue < 31.0f)
		{
			PlayerCharacter->GetSuitVoiceComponent()->Play(Oxygen30s);
			bOxygen30sGiven = true;
		}
	}

	// 60 seconds left warning (only if MaxValue > 60)
	if (MaxValue > 61.0f)
	{
		if (bOxygen60sGiven)
		{
			if (CurrentValue >= 61.0f)
				bOxygen60sGiven = false;
		}
		else
		{
			if (CurrentValue < 61.0f)
			{
				PlayerCharacter->GetSuitVoiceComponent()->Play(Oxygen60s);
				bOxygen60sGiven = true;
			}
		}
	}

	// Oxygen depleted warning
	if (bOxygenDepletedGiven)
	{
		if (CurrentValue > 0.5f)
			bOxygenDepletedGiven = false;
	}
	else
	{
		if (CurrentValue <= 0.5f)
		{
			PlayerCharacter->GetSuitVoiceComponent()->Play(OxygenDepleted);
			bOxygenDepletedGiven = true;
		}
	}
}
