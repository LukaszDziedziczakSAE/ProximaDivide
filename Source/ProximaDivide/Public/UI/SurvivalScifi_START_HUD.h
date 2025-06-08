// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SurvivalScifi_START_HUD.generated.h"

/**
 * 
 */
UCLASS()
class PROXIMADIVIDE_API ASurvivalScifi_START_HUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UUserWidget* StartScreen;

};
