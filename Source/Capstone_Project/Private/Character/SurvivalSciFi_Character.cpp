// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/SurvivalSciFi_Character.h"
#include "Item/InventoryComponent.h"
#include "Character/HealthComponent.h"
#include "Character/PaperdollComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableItemDataAsset.h"
#include "AkGameplayStatics.h"
#include "Kismet/GameplayStatics.h"

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

bool ASurvivalSciFi_Character::TryPickUpItem(UItemDataAsset* Item, bool bShowNotification)
{
	UEquipableItemDataAsset* Equipable = Cast<UEquipableItemDataAsset>(Item);
	if (Equipable != nullptr && PaperdollComponent->TryAddEquipable(Equipable)) return true;

	if (InventoryComponent->TryAddItem(Item, bShowNotification)) return true;

	return false;
}

void ASurvivalSciFi_Character::SelectSlot(int SlotNumber)
{
	if (!PaperdollComponent->DoesSlotHaveItem(SlotNumber)) return;

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

void ASurvivalSciFi_Character::Footstep()
{
	
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0,0,-150.0f);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
	if (Hit.bBlockingHit && Hit.GetActor() != nullptr)
	{
		switch (UGameplayStatics::GetSurfaceType(Hit))
		{
		case SurfaceType1:
			UAkGameplayStatics::SetSwitch(DirtValue, this);
			break;

		case SurfaceType2:
			UAkGameplayStatics::SetSwitch(InteriorValue, this);
			break;

		case SurfaceType3:
			UAkGameplayStatics::SetSwitch(MetalValue, this);
			break;

		default:
			TEnumAsByte<EPhysicalSurface> SurfaceType = UGameplayStatics::GetSurfaceType(Hit);
			UE_LOG(LogTemp, Warning, TEXT("Hit SurfaceType%s"), *FString::FromInt(SurfaceType.GetValue()));
		}
	}

	UAkGameplayStatics::PostEvent(FootstepEvent, this, int32(0), FOnAkPostEventCallback(), true);
}
