// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/HealthComponent.h"
#include "Character/OxygenComponent.h"
#include "Character/ExhaustionComponent.h"
#include "Character/SustenanceComponent.h"
#include "Character/PlayerInteractionComponent.h"
#include "Item/InventoryComponent.h"
#include "Character/PaperdollComponent.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableItemDataAsset.h"
#include "AkGameplayStatics.h"
#include "UI/SurvivalScifi_HUD.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	OxygenComponent = CreateDefaultSubobject<UOxygenComponent>(TEXT("Oxygen"));

	ExhaustionComponent = CreateDefaultSubobject<UExhaustionComponent>(TEXT("Exhaustion"));

	SustenanceComponent = CreateDefaultSubobject<USustenanceComponent>(TEXT("Sustenance"));

	PlayerInteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("Player Interaction Component"));

	FPS_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	FPS_Arms->SetupAttachment(CameraComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsAlive() && GetController<APlayerController>() != nullptr && GetHUD() != nullptr && !GetHUD()->IsShowingDeathScreen())
	{
		GetHUD()->HideInventory();
		GetHUD()->HideCraftingMenuOnly();
		GetHUD()->HideGameHUD();
		GetHUD()->HideInteraction();
		GetHUD()->ShowDeathScreen();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Interact()
{
	PlayerInteractionComponent->Interact();
}

void APlayerCharacter::SpawnHandItems()
{
	if (!PaperdollComponent->IsCurrentSlotHaveItem()) return;

	DespawnHandItems();

	if (PaperdollComponent->GetCurrentSlot().Item->RightHand != nullptr)
	{
		RightHandItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(PaperdollComponent->GetCurrentSlot().Item->RightHand);
		RightHandItem->AttachToComponent(FPS_Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHand"));
		RightHandItem->SetOwner(this);
		RightHandItem->UpdateRelatives();
	}

	if (PaperdollComponent->GetCurrentSlot().Item->LeftHand != nullptr)
	{
		LeftHandItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(PaperdollComponent->GetCurrentSlot().Item->LeftHand);
		LeftHandItem->AttachToComponent(FPS_Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeftHand"));
		LeftHandItem->SetOwner(this);
		LeftHandItem->UpdateRelatives();
	}
}

float APlayerCharacter::PlayMontage(UAnimMontage* Montage)
{
	return FPS_Arms->GetAnimInstance()->Montage_Play(Montage);
}

ASurvivalScifi_HUD* APlayerCharacter::GetHUD()
{
	return GetController<APlayerController>()->GetHUD<ASurvivalScifi_HUD>();;
}

void APlayerCharacter::ChangeStat(EStat StatType, float Amount)
{
	switch(StatType)
	{
	case EStat::Oxygen:
		OxygenComponent->ModifyValue(Amount);
		break;

	case EStat::Health:
		HealthComponent->ModifyValue(Amount);
		break;

	case EStat::Sustenance:
		SustenanceComponent->ModifyValue(Amount);
		break;

	case EStat::Exhaustion:
		ExhaustionComponent->ModifyValue(Amount);
		break;
	}
}

void APlayerCharacter::DropFromInventory(UItemDataAsset* DataAsset, FIntPoint Position)
{
	if (InventoryComponent->TryRemoveItemAt(DataAsset, Position))
	{
		AActor* Item = GetWorld()->SpawnActor(DataAsset->ItemClass);
		Item->SetActorLocation(CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * 50));
	}
}

void APlayerCharacter::DropFromPaperdoll(UItemDataAsset* DataAsset, int SlotNumber)
{
	if (PaperdollComponent->TryRemoveItemFromSlot(SlotNumber))
	{
		AActor* Item = GetWorld()->SpawnActor(DataAsset->ItemClass);
		Item->SetActorLocation(CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * 50));
	}
}

