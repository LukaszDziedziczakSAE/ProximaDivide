// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "Game/MissionDataAsset.h"
#include "Objectives_UserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UObjectives_UserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	class UPlayerObjectivesComponent* PlayerObjectives;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UObjective_UserWidget> ObjectiveUserWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TArray<UObjective_UserWidget*> ObjectiveUserWidgets;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MissionName;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ObjectivesBox;

	UFUNCTION()
	void SpawnWidget(UMissionDataAsset* NewMission, FObjectiveData NewObjective);

public:
	UFUNCTION()
	void UpdateObjectivesWidget();
	
};
