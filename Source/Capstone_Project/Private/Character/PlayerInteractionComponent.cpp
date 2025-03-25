// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/PlayerInteractionComponent.h"
#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Interface/Interaction.h"
#include "UI/SurvivalScifi_HUD.h"

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
		//UE_LOG(LogTemp, Warning, TEXT("Hit "));
		Cast<IInteraction>(Hit.GetActor());

		InteractionInterface.SetObject(Hit.GetActor());

		if (InteractionInterface.GetObject() != nullptr )
		{
			//UE_LOG(LogTemp, Warning, TEXT("Interactable "));

			HUD->ShowInteraction();
		}

	}

	else if (HUD->IsShowingInteraction())
	{
		
		HUD->HideInteraction();
		InteractionInterface.SetObject(nullptr);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Showing interaction: %s"), HUD->IsShowingInteraction() ? TEXT("true") : TEXT("false"));
	
}

FString UPlayerInteractionComponent::GetInteractionText()
{
	if (InteractionInterface.GetObject() == nullptr) return TEXT("");

	IInteraction* Interaction = Cast<IInteraction>(InteractionInterface.GetObject());

	if (Interaction == nullptr || Interaction->InteractionText() == TEXT(""))
		return TEXT("");

	return TEXT("Press E to ") + Interaction->InteractionText();
}

void UPlayerInteractionComponent::Interact()
{
	if (InteractionInterface.GetObject() == nullptr) return;
	IInteraction* Interaction = Cast<IInteraction>(InteractionInterface.GetObject());
	Interaction->Interact(PlayerCharacter);
}

