// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentValue = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxValue = 100.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetCurrentValue(){ return CurrentValue; }
	
	UFUNCTION(BlueprintPure)
	float GetMaxValue () { return MaxValue; }
	
	UFUNCTION(BlueprintPure)
	float GetPercentage() { return CurrentValue / MaxValue; }
};
