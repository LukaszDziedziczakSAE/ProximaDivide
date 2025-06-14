// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/MaintenanceComponent.h"
#include "Item/Crafting/ItemDataAsset.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Character/Player/PlayerCharacter.h"

// Sets default values for this component's properties
UMaintenanceComponent::UMaintenanceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMaintenanceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMaintenanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UMaintenanceComponent::IsFullyRepaired()
{
	for (FRepairSlot Slot : RepairSlots)
	{
		if (!Slot.IsRepaired())
		{
			return false;
		}
	}
	return true;
}

void UMaintenanceComponent::AddItem(int32 SlotIndex, UItemDataAsset* Item)
{
	if (RepairSlots.IsValidIndex(SlotIndex) && Item != nullptr)
	{
		RepairSlots[SlotIndex].CurrentItem = Item;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot index or item."));
	}
}

void UMaintenanceComponent::Repair(APlayerCharacter* playerCharacter)
{                  
	UE_LOG(LogTemp, Log, TEXT("Repairing item..."));
	PlayerCharacter = playerCharacter;
	ASurvivalScifi_HUD* HUD = PlayerCharacter->GetHUD();
	if (HUD == nullptr) return;

	if (!HUD->IsShowingRepairPanel())
	{
		UE_LOG(LogTemp, Log, TEXT("Showing Repair panel"))
		HUD->ShowRepairPanel();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Hiding Repair panel"))
		HUD->HideRepairPanel();
	}

}

