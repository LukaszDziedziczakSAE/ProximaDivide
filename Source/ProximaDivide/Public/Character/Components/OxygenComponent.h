// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/Components/StatComponent.h"
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

	UPROPERTY(EditAnywhere, Category = "Suit Voice")
	class UAkAudioEvent* OxygenLow;

	UPROPERTY(EditAnywhere, Category = "Suit Voice")
	class UAkAudioEvent* Oxygen50p;

	UPROPERTY(EditAnywhere, Category = "Suit Voice")
	class UAkAudioEvent* Oxygen30s;

	UPROPERTY(EditAnywhere, Category = "Suit Voice")
	class UAkAudioEvent* Oxygen60s;

	UPROPERTY(EditAnywhere, Category = "Suit Voice")
	class UAkAudioEvent* OxygenDepleted;

	UPROPERTY(EditAnywhere, Category = "Suit Voice")
	float LowOxygenThreshold = 5.0f;

	UPROPERTY(VisibleAnywhere)
	bool bOxygenLowGiven;

	UPROPERTY(VisibleAnywhere)
	bool bOxygen50pGiven;

	UPROPERTY(VisibleAnywhere)
	bool bOxygen30sGiven;

	UPROPERTY(VisibleAnywhere)
	bool bOxygen60sGiven;

	UPROPERTY(VisibleAnywhere)
	bool bOxygenDepletedGiven;

public:
	virtual FString GetLabel() override { return TEXT("O2"); }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
