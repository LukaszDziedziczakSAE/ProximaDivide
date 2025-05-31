// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "AI/Astronaut_AIController.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Character/TutorialGiverComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enviroment/Waypoint.h"

void AAstronaut_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TutorialGiver = PossesedCharacter->GetComponentByClass<UTutorialGiverComponent>();
	if (TutorialGiver != nullptr)
	{
		TutorialGiver->AI = this;

		if (TutorialBehaviorTree != nullptr)
		{

			RunBehaviorTree(TutorialBehaviorTree);
			UpdateBB();
		}
	}
}

void AAstronaut_AIController::UpdateBB()
{
	Super::UpdateBB();

	if (TutorialGiver != nullptr && GetBlackboardComponent() != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("TutorialRunning"), TutorialGiver->IsInProgress());
		GetBlackboardComponent()->SetValueAsBool(TEXT("TutorialComplete"), TutorialGiver->HasCompleted);

		if (!TutorialGiver->IsInProgress())
		{
			if (!TutorialGiver->HasCompleted && TutorialGiver->GetStartWaypoint() != nullptr)
			{
				GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoint"), TutorialGiver->GetStartWaypoint()->GetActorLocation());
			}
			else if (TutorialGiver->HasCompleted && TutorialGiver->GetEndWaypoint() != nullptr)
			{
				GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoint"), TutorialGiver->GetEndWaypoint()->GetActorLocation());
			}
		}
		
	}
}

void AAstronaut_AIController::BeginTutorial()
{
	if (TutorialGiver != nullptr && !TutorialGiver->HasCompleted && !TutorialGiver->IsInProgress())
	{
		TutorialGiver->BeginTutorial();
	}
}

void AAstronaut_AIController::PlaySitDownAnimation()
{
	if (TutorialGiver != nullptr && TutorialGiver->ReadyToSitDown())
	{
		TutorialGiver->PlaySitDownAnimation();

		if (TutorialGiver->GetFlightDeckChair() != nullptr)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoint"), TutorialGiver->GetFlightDeckChair()->GetActorLocation());
		}
	}
}
