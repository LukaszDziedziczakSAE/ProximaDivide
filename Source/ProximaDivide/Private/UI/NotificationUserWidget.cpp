// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/NotificationUserWidget.h"
#include "Components/TextBlock.h"
#include "Item/ItemDataAsset.h"

void UNotificationUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RewriteText();
}

void UNotificationUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Liftime -= InDeltaTime;
}

void UNotificationUserWidget::RewriteText()
{
	FString string = bRemoved ? "- " : "+ ";
	string += FString::FromInt(Quantity);
	string += " " + Item->Name;
	Text->SetText(FText::FromString(string));
}
