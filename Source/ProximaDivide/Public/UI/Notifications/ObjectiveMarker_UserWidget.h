// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "ObjectiveMarker_UserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UObjectiveMarker_UserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MarkerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MarkerDistance;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText MarkerText;

	UFUNCTION()
	void SetMarkerText(const FText& InText);
};
