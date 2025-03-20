// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OxygenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UOxygenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOxygenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentOxygen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxOxygen = 100.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetCurrentOxygen() { return CurrentOxygen; }

	UFUNCTION(BlueprintPure)
	float GetMaxOxygen() { return MaxOxygen; }

	UFUNCTION(BlueprintPure)
	float GetOxygenPercentage() { return CurrentOxygen / MaxOxygen; }

};
