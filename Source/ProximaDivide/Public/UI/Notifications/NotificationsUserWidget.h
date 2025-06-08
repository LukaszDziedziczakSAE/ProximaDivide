// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/SurvivalScifiUserWidget.h"
#include "NotificationsUserWidget.generated.h"

UCLASS()
class PROXIMADIVIDE_API UNotificationsUserWidget : public USurvivalScifiUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNotificationUserWidget> NotificationUserWidgetClass;

	UPROPERTY(EditAnywhere)
	float MessageLiftime{ 5.0f };

	UPROPERTY(VisibleAnywhere)
	TArray<UNotificationUserWidget*> Notifications;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* NotificationsBox;

public:
	UFUNCTION()
	void AddedItems(class UItemDataAsset* ItemDataAsset, int Amount);
	
	UFUNCTION()
	void RemovedItems(class UItemDataAsset* ItemDataAsset, int Amount);
};
