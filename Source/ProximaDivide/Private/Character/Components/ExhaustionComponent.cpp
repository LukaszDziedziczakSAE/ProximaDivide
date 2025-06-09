// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Components/ExhaustionComponent.h"

void UExhaustionComponent::Footstep()
{
	ModifyValue(PerFootstep);
}