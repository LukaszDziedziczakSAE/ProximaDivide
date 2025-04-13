// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "EAnimHandsType.generated.h"

UENUM(BlueprintType)
enum class EAnimHandsType : uint8
{
    None UMETA(DisplayName = "None"),
    TwoItems UMETA(DisplayName = "Two Items"),
    Pistol UMETA(DisplayName = "Pistol")
};