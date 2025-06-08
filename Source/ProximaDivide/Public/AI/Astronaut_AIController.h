// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "AI/SurvivalScifi_AIController.h"
#include "Astronaut_AIController.generated.h"

UCLASS()
class PROXIMADIVIDE_API AAstronaut_AIController : public ASurvivalScifi_AIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* TutorialBehaviorTree;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTutorialGiverComponent* TutorialGiver;

public:
	virtual void UpdateBB() override;

	UFUNCTION(BlueprintCallable)
	void BeginTutorial();

	UFUNCTION(BlueprintCallable)
	void PlaySitDownAnimation();
};
