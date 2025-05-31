// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerTutorialComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UPlayerTutorialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerTutorialComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	float CurrentThreshhold;

	UPROPERTY(EditAnywhere)
	float LookThreshhold = 50;

	UPROPERTY(EditAnywhere)
	float MovementThreshhold = 50;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	bool ShowMouseMoveInfo;

	UPROPERTY()
	bool ShowMovementInfo;

	UPROPERTY()
	bool ShowJumpInfo;

	UPROPERTY()
	bool SeenInventoryInfo;

	UPROPERTY()
	bool ShowInventoryInfo;

	UPROPERTY()
	bool SeenSlotInfo;

	UPROPERTY()
	bool ShowSlotInfo;

	UPROPERTY()
	bool HasSeenInventoryPickup;

	UPROPERTY()
	bool HasSeenInventoryDrop;

	UPROPERTY()
	bool ShowInventoryPickup = true;

	UPROPERTY()
	bool ShowInventoryDrop;

	UPROPERTY()
	class UTutorialGiverComponent* TutorialGiver;

	UFUNCTION()
	bool ShowingAnyInfo() {
		return ShowMouseMoveInfo
			|| ShowMouseMoveInfo
			|| ShowJumpInfo
			|| ShowInventoryInfo
			|| ShowSlotInfo;
	}

	UFUNCTION()
	void HasLooked(float LookAmount);

	UFUNCTION()
	void HasMovement(float MoveAmount);

	UFUNCTION()
	void HasJumped();

	UFUNCTION()
	void ItemPickedUp();

	UFUNCTION()
	void HasOpenedInventory();

	UFUNCTION()
	void HasClosedInventory();

	UFUNCTION()
	void ItemAddedToSlot();

	UFUNCTION()
	void HasUsedSlot();

	UFUNCTION()
	void InventoryPickUp();

	void InventoryDrop();
};
