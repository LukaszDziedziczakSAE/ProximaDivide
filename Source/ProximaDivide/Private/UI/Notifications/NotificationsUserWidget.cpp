// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "UI/Notifications/NotificationsUserWidget.h"
#include "UI/Notifications/NotificationUserWidget.h"
#include "Components/VerticalBox.h"

void UNotificationsUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TArray<UNotificationUserWidget*> DeadNotifications;
	for (UNotificationUserWidget* Notification : Notifications)
	{
		if (Notification->Liftime <= 0)
			DeadNotifications.Add(Notification);
	}
	for (UNotificationUserWidget* DeadNotification : DeadNotifications)
	{
		DeadNotification->RemoveFromParent();
		Notifications.Remove(DeadNotification);
	}

}

void UNotificationsUserWidget::AddedItems(UItemDataAsset* ItemDataAsset, int Amount)
{
	bool ModifiedExisting = false;
	for (UNotificationUserWidget* Notification : Notifications)
	{
		if (!Notification->bRemoved && Notification->Item == ItemDataAsset)
		{
			Notification->Liftime = MessageLiftime;
			Notification->Quantity += Amount;
			Notification->RewriteText();
			ModifiedExisting = true;
		}
	}

	if (!ModifiedExisting)
	{
		UNotificationUserWidget* Notification = CreateWidget<UNotificationUserWidget>(GetWorld(), NotificationUserWidgetClass);
		Notification->Item = ItemDataAsset;
		Notification->Quantity = Amount;
		Notification->bRemoved = false;
		Notification->Liftime = MessageLiftime;
		Notification->RewriteText();
		NotificationsBox->AddChildToVerticalBox(Notification);
		Notifications.Add(Notification);

		//UE_LOG(LogTemp, Warning, TEXT("New Add item notification"));
	}
}

void UNotificationsUserWidget::RemovedItems(UItemDataAsset* ItemDataAsset, int Amount)
{
	bool ModifiedExisting = false;
	for (UNotificationUserWidget* Notification : Notifications)
	{
		if (Notification->bRemoved && Notification->Item == ItemDataAsset)
		{
			Notification->Liftime = MessageLiftime;
			Notification->Quantity += Amount;
			Notification->RewriteText();
			ModifiedExisting = true;
		}
	}

	if (!ModifiedExisting)
	{
		UNotificationUserWidget* Notification = CreateWidget<UNotificationUserWidget>(GetWorld(), NotificationUserWidgetClass);
		Notification->Item = ItemDataAsset;
		Notification->Quantity = Amount;
		Notification->bRemoved = true;
		Notification->Liftime = MessageLiftime;
		Notification->RewriteText();
		NotificationsBox->AddChildToVerticalBox(Notification);
		Notifications.Add(Notification);
	}
}
