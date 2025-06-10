// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Notifications/Objective_UserWidget.h"
#include "Components/TextBlock.h"

void UObjective_UserWidget::SetObjectiveWidget(UMissionDataAsset* NewMission, FObjectiveData NewObjective)
{
	Mission = NewMission;
	Objective = NewObjective;

	ObjectiveText->SetText(Objective.Description);
}
