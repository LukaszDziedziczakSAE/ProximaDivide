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
#include "Item/EquipableSkItem.h"

// Sets default values
ASurvivalSciFi_Character::ASurvivalSciFi_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	PaperdollComponent = CreateDefaultSubobject<UPaperdollComponent>(TEXT("Paperdoll"));

	VoiceComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Voice Component"));
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

	if (!IsAlive())
	{
		DeathTimer -= DeltaTime;

		if (DeathTimer <= 0)
			Destroy();
	}
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
	//SpawnHandItems();

	if (PaperdollComponent->IsCurrentSlotHaveItem() 
		&& PaperdollComponent->GetCurrentSlot().Item->UseageMontage != nullptr)
	{
		//PlayMontage(PaperdollComponent->GetCurrentSlot().Item->UseageMontage);
		float t = PlayMontage(PaperdollComponent->GetCurrentSlot().Item->UseageMontage);

		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &ASurvivalSciFi_Character::SingleUseItemEnd, t, false);
	}
}

void ASurvivalSciFi_Character::SpawnHandItems()
{
	if (!PaperdollComponent->IsCurrentSlotHaveItem()) return;

	DespawnHandItems();

	if (PaperdollComponent->GetCurrentSlot().Item->RightHand != nullptr)
	{
		RightHandItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(PaperdollComponent->GetCurrentSlot().Item->RightHand);
		RightHandItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHand"));
		RightHandItem->SetOwner(this);
		RightHandItem->UpdateRelatives();
	}

	if (PaperdollComponent->GetCurrentSlot().Item->LeftHand != nullptr)
	{
		LeftHandItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(PaperdollComponent->GetCurrentSlot().Item->LeftHand);
		LeftHandItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeftHand"));
		LeftHandItem->SetOwner(this);
		LeftHandItem->UpdateRelatives();
	}
}

void ASurvivalSciFi_Character::DespawnHandItems()
{
	if (RightHandItem != nullptr)
	{
		RightHandItem->Destroy();
		RightHandItem = nullptr;
	}

	if (LeftHandItem != nullptr)
	{
		LeftHandItem->Destroy();
		LeftHandItem = nullptr;
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

void ASurvivalSciFi_Character::SingleUseItemEnd()
{
	PaperdollComponent->CurrentSlotSingleUseItem();
	DespawnHandItems();
}

void ASurvivalSciFi_Character::UseItem()
{
	if (RightHandItem == nullptr) return;

	AEquipableItem* EquipableItem = Cast<AEquipableItem>(RightHandItem);
	if (EquipableItem != nullptr)
	{
		EquipableItem->Use();
	}

	AEquipableSkItem* EquipableSkItem = Cast<AEquipableSkItem>(RightHandItem);
	if (EquipableSkItem != nullptr)
	{
		EquipableSkItem->Use();
	}
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

void ASurvivalSciFi_Character::ChangeStat(EStat StatType, float Amount)
{
	if (StatType == EStat::Health)
		HealthComponent->ModifyValue(Amount);
}

void ASurvivalSciFi_Character::DropFromInventory(UItemDataAsset* DataAsset, FIntPoint Position)
{
	if (InventoryComponent->TryRemoveItemAt(DataAsset, Position))
	{
		AActor* Item = GetWorld()->SpawnActor(DataAsset->ItemClass);
		Item->SetActorLocation(GetActorLocation() + DropSpawnOffset);
	}
}

void ASurvivalSciFi_Character::DropFromPaperdoll(UItemDataAsset* DataAsset, int SlotNumber)
{
	if (PaperdollComponent->TryRemoveItemFromSlot(SlotNumber))
	{
		AActor* Item = GetWorld()->SpawnActor(DataAsset->ItemClass);
		Item->SetActorLocation(GetActorLocation() + DropSpawnOffset);
	}
}

bool ASurvivalSciFi_Character::IsAlive()
{
	return HealthComponent->GetCurrentValue() > 0;
}
