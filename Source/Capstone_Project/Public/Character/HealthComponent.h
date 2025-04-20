// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/StatComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UHealthComponent : public UStatComponent
{
	GENERATED_BODY()

//public:	
//	// Sets default values for this component's properties
//	UHealthComponent();
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	float CurrentHealth;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	float MaxHealth = 100.0f;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	UFUNCTION(BlueprintPure)
//	float GetCurrentHealth(){ return CurrentHealth; }
//
//	UFUNCTION(BlueprintPure)
//	float GetMaxHealth() { return MaxHealth; }
//
//	UFUNCTION(BlueprintPure)
//	float GetHealthPercentage() { return CurrentHealth / MaxHealth; }
		
};
