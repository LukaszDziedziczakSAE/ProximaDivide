// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableSkItem.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"

AEquipableSkItem::AEquipableSkItem()
{
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEquipableSkItem::BeginPlay()
{
	Super::BeginPlay();

	PlayEquipSound();
}

void AEquipableSkItem::UpdateRelatives()
{
	SetActorRelativeLocation(RelativeLocation);
	SetActorRelativeRotation(RelativeRotation);
}

void AEquipableSkItem::PlayEquipSound()
{
	if (EquipSound != nullptr)
	{
		AudioComponent->PostAkEvent(EquipSound, int32(0), FOnAkPostEventCallback());
	}
}

void AEquipableSkItem::PlayUnequipSound()
{
	if (UnequipSound != nullptr)
	{
		AudioComponent->PostAkEvent(UnequipSound, int32(0), FOnAkPostEventCallback());
	}
}

void AEquipableSkItem::PlayUseSound()
{
	if (UseSound != nullptr)
	{
		AudioComponent->PostAkEvent(UseSound, int32(0), FOnAkPostEventCallback());
	}
}