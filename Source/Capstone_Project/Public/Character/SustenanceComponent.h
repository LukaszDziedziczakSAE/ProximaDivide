// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/StatComponent.h"
#include "SustenanceComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API USustenanceComponent : public UStatComponent
{
	GENERATED_BODY()

public:
	virtual FString GetLabel() override { return TEXT("Su"); }
	
};
