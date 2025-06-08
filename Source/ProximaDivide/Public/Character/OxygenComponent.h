// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/StatComponent.h"
#include "OxygenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UOxygenComponent : public UStatComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OutsideModifyPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InsideModifyPerSecond;

public:
	virtual FString GetLabel() override { return TEXT("O2"); }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
