// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotUserWidget.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API UInventorySlotUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint Position;
	
public:
	UFUNCTION(BlueprintPure)
	FIntPoint GetPosition() { return Position; }

	UFUNCTION()
	void SetPosition(FIntPoint NewPosition);

	UFUNCTION()
	void SetSize(float Size);
};
