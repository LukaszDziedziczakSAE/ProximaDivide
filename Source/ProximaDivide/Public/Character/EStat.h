// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "EStat.generated.h"

UENUM(BlueprintType)
enum class EStat : uint8
{
	NoStatType UMETA(DisplayName = "No Stat Type"),
	Oxygen UMETA(DisplayName = "Oxygen"),
	Health UMETA(DisplayName = "Health"),
	Sustenance UMETA(DisplayName = "Sustenance"),
	Exhaustion UMETA(DisplayName = "Exhaustion")
};

