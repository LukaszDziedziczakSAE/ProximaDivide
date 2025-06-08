// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalScifiStartMode.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASurvivalScifiStartMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class USurvivalSciFi_GameInstance* GameInstance;

public:
	virtual void BeginPlay() override;
	
};
