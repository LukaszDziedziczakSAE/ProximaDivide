// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "StatUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UStatUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(meta = (BindWidget))
	class UImage* Indicator;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ValueText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LabelText;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* ProgressMaterialPrefab;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* ProgressMaterial;

public:

	UPROPERTY()
	class UStatComponent* StatComponent;

	UFUNCTION()
	void UpdateStatWidget();
};
