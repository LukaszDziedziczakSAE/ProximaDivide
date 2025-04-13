// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableItem.h"
#include "Character/SurvivalSciFi_Character.h"
#include "AkGameplayStatics.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"
#include "Components/BoxComponent.h"

AEquipableItem::AEquipableItem()
{
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Collider->SetBoxExtent(FVector(0,0,0));
	Collider->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEquipableItem::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEquipableItem::UpdateRelatives()
{
	SetActorRelativeLocation(RelativeLocation);
	SetActorRelativeRotation(RelativeRotation);

	PlayEquipSound();
}

void AEquipableItem::Use()
{
	if (Busy) return;

	if (UseMontage != nullptr)
	{
		float t = GetOwner<ASurvivalSciFi_Character>()->PlayMontage(UseMontage);
		Busy = true;

		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &AEquipableItem::UseFinish, t * PercentageBusy, false);

		OnStartUsing.Broadcast();
	}

	
}

void AEquipableItem::UseFinish()
{
	Busy = false;
	if (Repeating && GetOwner<ASurvivalSciFi_Character>()->GetUseItemDown()) Use();

	OnEndUsing.Broadcast();
}

void AEquipableItem::PlayEquipSound()
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

	EquipSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}

void AEquipableItem::PlayUseSound()
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

	UseSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}

void AEquipableItem::TurnOnColliderOverlap()
{
	Collider->SetCollisionProfileName(TEXT("OverlapAll"));
}

void AEquipableItem::TurnOffColliderOverlap()
{

	Collider->SetCollisionProfileName(TEXT("NoCollision"));
}
