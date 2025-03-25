// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SwitchActivated.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USwitchActivated : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPSTONE_PROJECT_API ISwitchActivated
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void SwitchActivation() = 0;

	UFUNCTION()
	virtual FString InteractionText() = 0;
};
