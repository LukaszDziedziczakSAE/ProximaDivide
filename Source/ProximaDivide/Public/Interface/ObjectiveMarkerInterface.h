// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectiveMarkerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UObjectiveMarkerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for actors that can display an objective marker.
 */
class PROXIMADIVIDE_API IObjectiveMarkerInterface
{
	GENERATED_BODY()

public:
	virtual void ShowObjectiveMarker() = 0;
	virtual void HideObjectiveMarker() = 0;
};
