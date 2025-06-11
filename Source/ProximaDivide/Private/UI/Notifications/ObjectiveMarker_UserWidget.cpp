// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Notifications/ObjectiveMarker_UserWidget.h"
#include "Components/TextBlock.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/WidgetComponent.h"

void UObjectiveMarker_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MarkerName->SetText(MarkerText);
	MarkerDistance->SetText(FText::FromString(""));

	/*if (UWidgetComponent* WidgetComp = Cast<UWidgetComponent>(GetTypedOuter<UWidgetComponent>()))
	{
		Owner = WidgetComp->GetOwner();
	}

	if (Owner == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectiveMarker_UserWidget: Owner is null!"));
		return;
	}*/
}

void UObjectiveMarker_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (Owner == nullptr || Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ObjectiveMarker_UserWidget: Owner or Player is null!"));
		return;
	}

	float Distance = FVector::Distance(Player->GetActorLocation(), Owner->GetComponentLocation());
	Distance /= 100; // Convert to meters
	Distance = FMath::FloorToFloat(Distance);
	MarkerDistance->SetText(FText::FromString(FString::SanitizeFloat(Distance, 0) + "m"));
}

void UObjectiveMarker_UserWidget::SetMarkerText(const FText& InText)
{
	MarkerText = InText;
	if (MarkerName)
	{
		MarkerName->SetText(MarkerText);
	}
}
