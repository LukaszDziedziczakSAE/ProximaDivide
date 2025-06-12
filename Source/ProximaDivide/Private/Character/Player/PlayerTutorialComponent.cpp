// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerTutorialComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Character/Components/TutorialGiverComponent.h"

// Sets default values for this component's properties
UPlayerTutorialComponent::UPlayerTutorialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentThreshhold = 0;
	
}


// Called every frame
void UPlayerTutorialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerTutorialComponent::HasLooked(float LookAmount)
{
	if (ShowMouseMoveInfo)
	{
		CurrentThreshhold += LookAmount;

		if (CurrentThreshhold >= LookThreshhold)
		{
			CurrentThreshhold = 0;
			ShowMouseMoveInfo = false;
			//ShowMovementInfo = true;

			GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();

			if (TutorialGiver != nullptr && TutorialGiver->IsInProgress() &&
				TutorialGiver->GetCurrentPart().TutorialCondition == OnLookAround)
			{
				TutorialGiver->GoToNextPart();
			}
		}
	}
}

void UPlayerTutorialComponent::HasMovement(float MoveAmount, bool bIsSprinting)
{
	if (ShowMovementInfo)
	{
		CurrentThreshhold += MoveAmount;
		if (CurrentThreshhold >= MovementThreshhold)
		{
			ShowMovementInfo = false;
			//ShowJumpInfo = true;
			GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();

			if (TutorialGiver != nullptr && TutorialGiver->IsInProgress() &&
				TutorialGiver->GetCurrentPart().TutorialCondition == OnMoveAround)
			{
				TutorialGiver->GoToNextPart();
			}
		}
	}

	if (bIsSprinting)
	{
		if (ShowSprintInfo)
		{
			TutorialState.HasSeenSprintInfo = true;
			ShowSprintInfo = false;
			GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
		}
	}
}

void UPlayerTutorialComponent::HasJumped()
{
	if (ShowJumpInfo)
	{
		TutorialState.SeenJumpInfo = true;
		ShowJumpInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::ItemPickedUp()
{
	if (!TutorialState.SeenInventoryInfo && !ShowingAnyInfo())
	{
		TutorialState.SeenInventoryInfo = true;
		ShowInventoryInfo = true;

		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::HasOpenedInventory()
{
	if (ShowInventoryInfo)
	{
		ShowInventoryInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}

	if (TutorialGiver != nullptr && TutorialGiver->IsInProgress() &&
		TutorialGiver->GetCurrentPart().TutorialCondition == OpenInventory)
	{
		TutorialGiver->GoToNextPart();
	}
}

void UPlayerTutorialComponent::HasClosedInventory()
{
	if (TutorialGiver != nullptr && TutorialGiver->IsInProgress() &&
		TutorialGiver->GetCurrentPart().TutorialCondition == ClosedInventory)
	{
		TutorialGiver->GoToNextPart();
	}
}

void UPlayerTutorialComponent::ItemAddedToSlot()
{
	if (TutorialGiver != nullptr && TutorialGiver->IsInProgress() &&
		TutorialGiver->GetCurrentPart().TutorialCondition == PickupItem)
	{
		TutorialGiver->GoToNextPart();
	}
}

void UPlayerTutorialComponent::HasUsedSlot()
{
	if (ShowSlotInfo)
	{
		ShowSlotInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}

	if (TutorialGiver != nullptr && TutorialGiver->IsInProgress() &&
		TutorialGiver->GetCurrentPart().TutorialCondition == ConsumeItem)
	{
		TutorialGiver->GoToNextPart();
	}
}

void UPlayerTutorialComponent::InventoryPickUp()
{
	if (ShowInventoryPickup)
	{
		TutorialState.HasSeenInventoryPickup = true;
		ShowInventoryPickup = false;
		if (!TutorialState.HasSeenInventoryDrop) ShowInventoryDrop = true;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::InventoryDrop()
{
	if (ShowInventoryDrop)
	{
		ShowInventoryDrop = false;
		TutorialState.HasSeenInventoryDrop = true;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::SkipTutorial()
{
	if (TutorialGiver != nullptr && TutorialGiver->IsInProgress())
	{
		TutorialGiver->StopTalkingAnimation();
		TutorialGiver->CompleteTutorial();
	}
}

void UPlayerTutorialComponent::HasTurnOnLight()
{
	TutorialState.HasSeenLightInfo = true;
	if (ShowLightInfo)
	{
		ShowLightInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}
