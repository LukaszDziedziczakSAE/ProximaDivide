// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/SurvivalSciFi_Character.h"
#include "Item/InventoryComponent.h"
#include "Character/HealthComponent.h"
#include "Character/PaperdollComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableItemDataAsset.h"

// Sets default values
ASurvivalSciFi_Character::ASurvivalSciFi_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	PaperdollComponent = CreateDefaultSubobject<UPaperdollComponent>(TEXT("Paperdoll"));
}

// Called when the game starts or when spawned
void ASurvivalSciFi_Character::BeginPlay()
{
	Super::BeginPlay();
	SetMovementSpeed(false);
}

// Called every frame
void ASurvivalSciFi_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASurvivalSciFi_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASurvivalSciFi_Character::SetMovementSpeed(bool IsRunning)
{
	GetCharacterMovement()->MaxWalkSpeed = IsRunning ? RunningSpeed : WalkingSpeed;
}

bool ASurvivalSciFi_Character::TryPickUpItem(UItemDataAsset* Item)
{
	UEquipableItemDataAsset* Equipable = Cast<UEquipableItemDataAsset>(Item);
	if (Equipable != nullptr && PaperdollComponent->TryAddEquipable(Equipable)) return true;

	if (InventoryComponent->TryAddItem(Item)) return true;

	return false;
}

void ASurvivalSciFi_Character::SelectSlot(int SlotNumber)
{
	PaperdollComponent->SelectSlot(SlotNumber);
	SpawnRightHand();
}

void ASurvivalSciFi_Character::SpawnRightHand()
{
	DespawnRightHand();

	if (PaperdollComponent->IsCurrentSlotHaveItem())
	{
		RightHandItem = GetWorld()->SpawnActor<AEquipableItem>(PaperdollComponent->GetCurrentSlot().Item->RightHand);
		RightHandItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHand"));
		RightHandItem->UpdateRelatives();
		RightHandItem->SetOwner(this);
	}
}

void ASurvivalSciFi_Character::DespawnRightHand()
{
	if (RightHandItem != nullptr)
	{
		RightHandItem->Destroy();
		RightHandItem = nullptr;
	}
}

void ASurvivalSciFi_Character::UseItemRepeating()
{
	UseItem();
	UseItemDown = true;
}

void ASurvivalSciFi_Character::UseItemEnd()
{
	UseItemDown = false;
}

void ASurvivalSciFi_Character::UseItem()
{
	if (RightHandItem == nullptr) return;

	RightHandItem->Use();
}

float ASurvivalSciFi_Character::PlayMontage(UAnimMontage* Montage)
{
	return GetMesh()->GetAnimInstance()->Montage_Play(Montage);
}
