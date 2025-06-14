// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Repair.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URepair : public UInterface
{
	GENERATED_BODY()
};


class PROXIMADIVIDE_API IRepair
{
    GENERATED_BODY()

public:
    // Must be implemented to return the MaintenanceComponent
    UFUNCTION()
    virtual class UMaintenanceComponent* GetMaintenanceComponent() const = 0;

    // Must be implemented to return the repair interaction box (collision)
    UFUNCTION()
    virtual class UBoxComponent* GetRepairInteractionZone() const = 0;

    UFUNCTION()
    virtual void Repair(class APlayerCharacter* PlayerCharacter) const = 0;
};
