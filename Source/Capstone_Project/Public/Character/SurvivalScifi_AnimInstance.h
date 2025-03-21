// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SurvivalScifi_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API USurvivalScifi_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Angle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;
	
	UPROPERTY(VisibleAnywhere)
	class ASurvivalSciFi_Character* Character;

public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
