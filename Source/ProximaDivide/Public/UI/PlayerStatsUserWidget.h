// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "PlayerStatsUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UPlayerStatsUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UStatUserWidget* OxygenStat;

	UPROPERTY(meta = (BindWidget))
	UStatUserWidget* HealthStat;

	UPROPERTY(meta = (BindWidget))
	UStatUserWidget* SustenanceStat;

	UPROPERTY(meta = (BindWidget))
	UStatUserWidget* ExhaustionStat;
};
