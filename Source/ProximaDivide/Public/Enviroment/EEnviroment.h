// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "EEnviroment.generated.h"

UENUM(BlueprintType)
enum class EEnviroment : uint8
{
    NoEnviroment UMETA(DisplayName = "No Enviroment"),
    Menu UMETA(DisplayName = "Menu"),
    Inside UMETA(DisplayName = "Inside"),
    Outside UMETA(DisplayName = "Outside"),
    DecentCinematic UMETA(DisplayName = "Decent Cinematic"),
    Ship UMETA(DisplayName = "Ship"),
    PostCrash UMETA(DisplayName = "Post Crash")
};
