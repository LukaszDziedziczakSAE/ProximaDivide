// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "PlayerTutorialComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROXIMADIVIDE_API UPlayerTutorialComponent : public UActorComponent
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	FTutorialState TutorialState;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	class UTutorialGiverComponent* TutorialGiver;

	UPROPERTY()
	bool ShowMouseMoveInfo;

	UPROPERTY()
	bool ShowMovementInfo;

	UPROPERTY()
	bool ShowSprintInfo;

	UPROPERTY()
	bool ShowJumpInfo;

	UPROPERTY()
	bool ShowInventoryInfo;

	UPROPERTY()
	bool ShowSlotInfo;

	UPROPERTY()
	bool ShowLightInfo;

	UPROPERTY()
	bool ShowInventoryPickup;

	UPROPERTY()
	bool ShowInventoryDrop;

	UPROPERTY()
	bool HideStats;

	UPROPERTY()
	bool HideActionBar;

	UPROPERTY()
	bool HideDayTime;

	UPROPERTY()
	bool PreventMovement;

	UPROPERTY()
	bool PreventLook;

	UPROPERTY()
	bool PreventInteract;

	UPROPERTY()
	bool PreventActionBarUse;

	UPROPERTY()
	bool PreventInventoryOpen;

	UFUNCTION()
	bool ShowingAnyInfo() {
		return ShowMouseMoveInfo
			|| ShowMovementInfo
			|| ShowSprintInfo
			|| ShowJumpInfo
			|| ShowInventoryInfo
			|| ShowSlotInfo
			|| ShowLightInfo
			|| ShowInventoryPickup
			|| ShowInventoryDrop;
	}

	UFUNCTION()
	void HasLooked(float LookAmount);

	UFUNCTION()
	void HasMovement(float MoveAmount, bool bIsSprinting);

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

	UFUNCTION()
	void SkipTutorial();

	UFUNCTION()
	void HasTurnOnLight();

	UFUNCTION(BlueprintCallable)
	const FTutorialState& GetTutorialState() const { return TutorialState; }

	UFUNCTION(BlueprintCallable)
	void SetTutorialState(const FTutorialState& NewState) { TutorialState = NewState; }

	// Optionally, individual setters/getters for each flag:
	UFUNCTION(BlueprintCallable)
	bool GetSeenInventoryInfo() const { return TutorialState.SeenInventoryInfo; }
	
	UFUNCTION(BlueprintCallable)
	void SetSeenInventoryInfo(bool bValue) { TutorialState.SeenInventoryInfo = bValue; }
};
