// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UNotificationUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text;

public:

	UPROPERTY(VisibleAnywhere)
	class UItemDataAsset* Item;
	
	UPROPERTY(VisibleAnywhere)
	int Quantity;

	UPROPERTY(VisibleAnywhere)
	bool bRemoved;

	UPROPERTY(VisibleAnywhere)
	float Liftime{ 5.0f };

	UFUNCTION()
	void RewriteText();
};
