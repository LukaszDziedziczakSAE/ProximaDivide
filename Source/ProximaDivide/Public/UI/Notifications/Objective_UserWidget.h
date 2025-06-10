// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/MissionDataAsset.h"
#include "Objective_UserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UObjective_UserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ObjectiveText;

	UPROPERTY(VisibleAnywhere)
	UMissionDataAsset* Mission;

	UPROPERTY(VisibleAnywhere)
	FObjectiveData Objective;

public:
	UFUNCTION()
	void SetObjectiveWidget(UMissionDataAsset* NewMission, FObjectiveData NewObjective);

	UMissionDataAsset* GetMission() { return Mission; }

	FObjectiveData GetObjective() { return Objective; }

};
