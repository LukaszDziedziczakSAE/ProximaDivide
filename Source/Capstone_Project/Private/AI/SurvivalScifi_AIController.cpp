// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "AI/SurvivalScifi_AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SurvivalSciFi_Character.h"

ASurvivalScifi_AIController::ASurvivalScifi_AIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASurvivalScifi_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASurvivalScifi_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossesedCharacter = Cast<ASurvivalSciFi_Character>(InPawn);
	RunBehaviorTree(BehaviorTree);
}

void ASurvivalScifi_AIController::UpdateBB()
{
}
