// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/SurvivalScifi_Item.h"
#include "EquipableItem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API AEquipableItem : public ASurvivalScifi_Item
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	FVector RelativeLocation;

	UPROPERTY(EditDefaultsOnly)
	FQuat RelativeRotation;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* UseMontage;

	UPROPERTY(EditDefaultsOnly)
	float PercentageBusy{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	bool Repeating;

	UPROPERTY(VisibleAnywhere)
	bool Busy;

public:
	UFUNCTION()
	void UpdateRelatives();
	
	UFUNCTION()
	virtual void Use();

	UFUNCTION()
	virtual void UseFinish();

	UFUNCTION()
	UAnimMontage* GetUseMontage() { return UseMontage; }
};
