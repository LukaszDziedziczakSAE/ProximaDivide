// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/Components/StatComponent.h"
#include "ExhaustionComponent.generated.h"

UCLASS()
class PROXIMADIVIDE_API UExhaustionComponent : public UStatComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PerFootstep = 1;

public:
	virtual FString GetLabel() override { return TEXT("Ex"); }

	UFUNCTION()
	void Footstep();
	
};
