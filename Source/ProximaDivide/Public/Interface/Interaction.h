// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

class PROXIMADIVIDE_API IInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void Interact(class APlayerCharacter* PlayerCharacter) = 0;

	UFUNCTION()
	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) = 0;

	UFUNCTION()
	virtual void InteractAlternative(class APlayerCharacter* PlayerCharacter) {}

};
