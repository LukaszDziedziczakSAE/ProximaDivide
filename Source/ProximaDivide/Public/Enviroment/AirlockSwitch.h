// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Enviroment/Switch.h"
#include "AirlockSwitch.generated.h"

UENUM(BlueprintType)
enum class EAirlockSwitchSide : uint8
{
	Outer UMETA(DisplayName = "Outer"),
	Inner UMETA(DisplayName = "Inner"),
	InsideOuter UMETA(DisplayName = "Inside Outer"),
	InsideInner UMETA(DisplayName = "Inside Inner")
};

UCLASS()
class PROXIMADIVIDE_API AAirlockSwitch : public ASwitch
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class AAirlock* Airlock;

	UPROPERTY(EditAnywhere)
	EAirlockSwitchSide AirlockSwitchSide;

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText() override;
	
};
