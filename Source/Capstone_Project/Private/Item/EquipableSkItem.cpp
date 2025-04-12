// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableSkItem.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"
#include "Components/BoxComponent.h"

AEquipableSkItem::AEquipableSkItem()
{
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Collider->SetBoxExtent(FVector(0, 0, 0));
	Collider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AEquipableSkItem::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipableSkItem::UpdateRelatives()
{
	SetActorRelativeLocation(RelativeLocation);
	SetActorRelativeRotation(RelativeRotation);

	PlayEquipSound();
}

void AEquipableSkItem::PlayEquipSound()
{
	if (AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing AudioComponent reference"));
		return;
	}
	if (EquipSound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing EquipSound reference"));
		return;
	}

	//AudioComponent->PostAkEvent(EquipSound, int32(0), FOnAkPostEventCallback());
	EquipSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}

void AEquipableSkItem::PlayUnequipSound()
{
	if (AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing AudioComponent reference"));
		return;
	}
	if (UnequipSound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing UnequipSound reference"));
		return;
	}

	AudioComponent->PostAkEvent(UnequipSound, int32(0), FOnAkPostEventCallback());
}

void AEquipableSkItem::PlayUseSound()
{
	if (AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing AudioComponent reference"));
		return;
	}
	if (UseSound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing UseSound reference"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Playing Use Sound"));
	//AudioComponent->PostAkEvent(UseSound, int32(0), FOnAkPostEventCallback());
	UseSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}