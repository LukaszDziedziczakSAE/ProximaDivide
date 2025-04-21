// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/StatUserWidget.h"
#include "Character/StatComponent.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UStatUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressMaterial = UMaterialInstanceDynamic::Create(ProgressMaterialPrefab, this);
}

void UStatUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateStatWidget();
}

void UStatUserWidget::UpdateStatWidget()
{
	if (StatComponent != nullptr)
	{
		LabelText->SetText(FText::FromString(StatComponent->GetLabel()));

		if (StatComponent->GetLabel() == TEXT("O2"))
			ValueText->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundToDouble(StatComponent->GetCurrentValue()), 0) + "s"));
		else
			ValueText->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundToDouble((StatComponent->GetPercentage() * 100)), 0) + "%"));

		ProgressMaterial->SetScalarParameterValue(TEXT("Percentage"), (StatComponent->GetPercentage() * 0.7f));
		Indicator->SetBrushFromMaterial(ProgressMaterial);
	}
}
