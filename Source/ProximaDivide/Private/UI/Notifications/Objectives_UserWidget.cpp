// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Notifications/Objectives_UserWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerObjectivesComponent.h"
#include "UI/Notifications/Objective_UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UObjectives_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerCharacter == nullptr) return;

	PlayerObjectives = PlayerCharacter->GetObjectivesComponent();

	UpdateObjectivesWidget();
}

void UObjectives_UserWidget::SpawnWidget(UMissionDataAsset* NewMission, FObjectiveData NewObjective)
{
	UObjective_UserWidget* Widget = CreateWidget<UObjective_UserWidget>(GetWorld(), ObjectiveUserWidgetClass);
	Widget->SetObjectiveWidget(NewMission, NewObjective);
	ObjectiveUserWidgets.Add(Widget);
	ObjectivesBox->AddChildToVerticalBox(Widget);
}

void UObjectives_UserWidget::UpdateObjectivesWidget()
{
	if (PlayerObjectives == nullptr) return;

	if (PlayerObjectives->HasMissions())
	{
		UMissionDataAsset* CurrentMission = PlayerObjectives->GetCurrentMission();
		MissionName->SetText(CurrentMission->MissionName);

		if (!CurrentMission->bMultiObjective)
		{
			FObjectiveData CurrentObjective = PlayerObjectives->GetCurrentObjective();

			if (ObjectiveUserWidgets.Num() > 0)
			{
				bool CurrentObjectiveDisplayed = false;
				TArray<UObjective_UserWidget*> WidgetsToRemove;
				for (UObjective_UserWidget* Widget : ObjectiveUserWidgets)
				{
					if (CurrentMission != Widget->GetMission() || CurrentObjective != Widget->GetObjective())
					{
						WidgetsToRemove.Add(Widget);
					}
					else
					{
						CurrentObjectiveDisplayed = true;
					}
				}
				for (UObjective_UserWidget* Widget : WidgetsToRemove)
				{
					ObjectivesBox->RemoveChild(Widget);
					ObjectiveUserWidgets.Remove(Widget);
				}
				if (!CurrentObjectiveDisplayed)
				{
					SpawnWidget(CurrentMission, CurrentObjective);
				}
			}

			else
			{
				SpawnWidget(CurrentMission, CurrentObjective);
			}
		}
		else
		{
			// multi objective logic
		}
	}

	else
	{
		MissionName->SetText(FText::FromString(""));
	}
}