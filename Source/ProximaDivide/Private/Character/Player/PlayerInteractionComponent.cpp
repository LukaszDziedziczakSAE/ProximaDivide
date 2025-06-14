// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerInteractionComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Interface/Interaction.h"
#include "Interface/Repair.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Enviroment/CraftingMachine.h"
#include "Item/SurvivalScifi_Item.h"
#include "AkGameplayStatics.h"
#include "Enviroment/Container.h"
#include "Character/Player/PlayerObjectivesComponent.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>();
}


void UPlayerInteractionComponent::InputModeUI(bool UIMode)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->SetShowMouseCursor(UIMode);
	if (UIMode)
		PlayerController->SetInputMode(FInputModeGameAndUI());
	else
		PlayerController->SetInputMode(FInputModeGameOnly());
	IsInUIMode = UIMode;
}

// Called every frame
void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter == nullptr || HUD == nullptr) return;

	FHitResult Hit;
	FVector Start = PlayerCharacter->GetCameraComponent()->GetComponentLocation();
	FVector End = Start + (PlayerCharacter->GetCameraComponent()->GetForwardVector() * Distance);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, -1.0f, 0, 1.0f);

	if (Hit.bBlockingHit)
	{
		AActor* HitActor = Hit.GetActor();
		UPrimitiveComponent* HitComponent = Hit.GetComponent();
		bool ShowInteraction = false;

		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteraction::StaticClass()))
		{
			InteractionInterface.SetObject(HitActor);
			ShowInteraction = true;
		}
		else
		{
			InteractionInterface.SetObject(nullptr);
		}

		// Only set repair interface if component has "RepairZone" tag
		if (HitComponent && HitComponent->ComponentHasTag("RepairZone") &&
			HitActor && HitActor->GetClass()->ImplementsInterface(URepair::StaticClass()))
		{
			RepairInterface.SetObject(HitActor);
			IsRepairInteraction = true;
		}
		else
		{
			RepairInterface.SetObject(nullptr);
			IsRepairInteraction = false;
		}

		if (ShowInteraction && !HUD->IsShowingInteraction())
		{
			HUD->ShowInteraction();
		}
		else if (!ShowInteraction && HUD->IsShowingInteraction())
		{
			HUD->HideInteraction();
		}
	}

	else if (HUD->IsShowingInteraction())
	{
		IsRepairInteraction = false;
		InteractionInterface.SetObject(nullptr);
		RepairInterface.SetObject(nullptr);

		if (HUD->IsShowingInteraction())
			HUD->HideInteraction();
	}
}

FString UPlayerInteractionComponent::GetInteractionText()
{
	if (PlayerCharacter->PreventInteraction()
		|| InteractionInterface.GetObject() == nullptr)
		return TEXT("");

	if (IsRepairInteraction)
	{
		if (!HUD->IsShowingRepairPanel())
		{
			return TEXT("Press E to Open Maintenance Panel");
		}

		else return TEXT("");
	}

	else
	{
		IInteraction* Interaction = Cast<IInteraction>(InteractionInterface.GetObject());
		FString InteractionText = Interaction->InteractionText(PlayerCharacter);

		if (Interaction == nullptr || InteractionText == TEXT(""))
			return TEXT("");

		return TEXT("Press E to ") + InteractionText;
	}
	
}

void UPlayerInteractionComponent::Interact()
{
	if (InteractionInterface.GetObject() == nullptr) return;

	if (IsRepairInteraction)
	{
		IRepair* Repair = Cast<IRepair>(RepairInterface.GetObject());
		if (Repair != nullptr) Repair->Repair(PlayerCharacter);
		HUD->ResetInteraction();
	}

	else
	{
		AActor* Actor = Cast<AActor>(InteractionInterface.GetObject());
		if (Actor != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Interaction with %s"), *Actor->GetName());

			if (Actor->Tags.Num() > 0)
				PlayerCharacter->GetObjectivesComponent()->OnInteractWithActor(Actor->Tags[0]);

			//else UE_LOG(LogTemp, Warning, TEXT("Interaction actor has no tags"));
		}

		ASurvivalScifi_Item* Item = Cast<ASurvivalScifi_Item>(InteractionInterface.GetObject());
		if (Item != nullptr)
		{
			UAkGameplayStatics::PostEvent(PickUpSound, Item, int32(0), FOnAkPostEventCallback(), false);
		}

		IInteraction* Interaction = Cast<IInteraction>(InteractionInterface.GetObject());
		if (Interaction != nullptr) Interaction->Interact(PlayerCharacter);
		HUD->ResetInteraction();
	}
	
}

bool UPlayerInteractionComponent::InteractableIsCraftingMachine()
{
	class ACraftingMachine* CraftingMachine = Cast<ACraftingMachine>(InteractionInterface.GetObject());

	return CraftingMachine != nullptr;
}

ACraftingMachine* UPlayerInteractionComponent::GetCraftingMachine()
{
	if (InteractionInterface.GetObject() == nullptr) return nullptr;
	return Cast<ACraftingMachine>(InteractionInterface.GetObject());
}

AContainer* UPlayerInteractionComponent::GetContainer()
{
	if (InteractionInterface.GetObject() == nullptr) return nullptr;
	return Cast<AContainer>(InteractionInterface.GetObject());
}

bool UPlayerInteractionComponent::IsLookingAtRepairZone()
{
	return IsRepairInteraction;
	//return RepairInterface.GetObject() != nullptr;
}

UMaintenanceComponent* UPlayerInteractionComponent::GetRepairComponent() const
{
	if (!RepairInterface.GetObject()) return nullptr;

	const AActor* RepairActor = Cast<AActor>(RepairInterface.GetObject());
	if (RepairActor == nullptr|| !RepairActor->GetClass()->ImplementsInterface(URepair::StaticClass()))
		return nullptr;

	const IRepair* Repair = Cast<IRepair>(RepairActor);
	if (Repair == nullptr) return nullptr;

	return Repair->GetMaintenanceComponent();
}

