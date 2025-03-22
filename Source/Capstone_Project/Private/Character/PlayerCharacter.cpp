// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/OxygenComponent.h"
#include "Character/PlayerInteractionComponent.h"
#include "Item/InventoryComponent.h"
#include "Character/PaperdollComponent.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableItemDataAsset.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	OxygenComponent = CreateDefaultSubobject< UOxygenComponent>(TEXT("Oxygen"));

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

void APlayerCharacter::SpawnRightHand()
{
	DespawnRightHand();

	if (PaperdollComponent->IsCurrentSlotHaveItem())
	{
		RightHandItem = GetWorld()->SpawnActor<AEquipableItem>(PaperdollComponent->GetCurrentSlot().Item->RightHand);
		RightHandItem->AttachToComponent(FPS_Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHand"));
		RightHandItem->UpdateRelatives();
		RightHandItem->SetOwner(this);
	}
}

float APlayerCharacter::PlayMontage(UAnimMontage* Montage)
{
	return FPS_Arms->GetAnimInstance()->Montage_Play(Montage);
}

