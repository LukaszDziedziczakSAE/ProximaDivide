// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/EAnimHandsType.h"
#include "SurvivalScifi_AnimInstance.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API USurvivalScifi_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Angle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASurvivalSciFi_Character* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnimHandsType AnimHandsType;

	UFUNCTION()
	void UpdateHandsType();

	UFUNCTION(BlueprintCallable)
	void SpawnHandItems();

	UFUNCTION(BlueprintCallable)
	void DespawnHandItems();

public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
