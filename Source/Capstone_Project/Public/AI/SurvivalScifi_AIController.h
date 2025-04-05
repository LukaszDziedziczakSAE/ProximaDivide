// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SurvivalScifi_AIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;

UCLASS()
class CAPSTONE_PROJECT_API ASurvivalScifi_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ASurvivalScifi_AIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;

public:
	

private:
	
};
