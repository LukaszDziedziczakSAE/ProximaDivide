// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/StatComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UHealthComponent : public UStatComponent
{
	GENERATED_BODY()

public:
	virtual FString GetLabel() override { return TEXT("HP"); }
		
};
