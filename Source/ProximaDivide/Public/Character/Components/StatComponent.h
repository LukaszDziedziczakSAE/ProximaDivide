// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentValue = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxValue = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ModifyPerSecond;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* PlayerCharacter;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetCurrentValue(){ return CurrentValue; }
	
	UFUNCTION(BlueprintPure)
	float GetMaxValue () { return MaxValue; }
	
	UFUNCTION(BlueprintPure)
	float GetPercentage() { return CurrentValue / MaxValue; }

	UFUNCTION(BlueprintPure)
	float GetMissingValue() { return MaxValue - CurrentValue; }

	UFUNCTION(BlueprintPure)
	float GetMissingPercentage() { return 1.0 - GetPercentage(); }

	UFUNCTION(BlueprintCallable)
	void ModifyValue(float ModifyAmount);

	UFUNCTION(BlueprintCallable)
	void SetValue(float NewValue) { CurrentValue = NewValue; }

	UFUNCTION(BlueprintCallable)
	virtual FString GetLabel() { return TEXT("xx"); }
};
