// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableItem.h"
#include "Character/SurvivalSciFi_Character.h"
#include "AkGameplayStatics.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"

AEquipableItem::AEquipableItem()
{
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
}

void AEquipableItem::BeginPlay()
{
	Super::BeginPlay();

	PlayEquipSound();
}

void AEquipableItem::UpdateRelatives()
{
	SetActorRelativeLocation(RelativeLocation);
	SetActorRelativeRotation(RelativeRotation);
}

void AEquipableItem::Use()
{
	if (Busy) return;

	if (UseMontage != nullptr)
	{
		//float t = GetOwner<ASurvivalSciFi_Character>()->PlayAnimMontage(UseMontage);
		float t = GetOwner<ASurvivalSciFi_Character>()->PlayMontage(UseMontage);
		Busy = true;

		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &AEquipableItem::UseFinish, t * PercentageBusy, false);
	}

	OnStartUsing.Broadcast();
}

void AEquipableItem::UseFinish()
{
	Busy = false;
	if (GetOwner<ASurvivalSciFi_Character>()->GetUseItemDown()) Use();

	OnEndUsing.Broadcast();
}

void AEquipableItem::PlayEquipSound()
{
	if (EquipSound != nullptr)
	{
		AudioComponent->PostAkEvent(EquipSound, int32(0), FOnAkPostEventCallback());
	}
}

void AEquipableItem::PlayUnequipSound()
{
	if (UnequipSound != nullptr)
	{
		AudioComponent->PostAkEvent(UnequipSound, int32(0), FOnAkPostEventCallback());
	}
}

void AEquipableItem::PlayUseSound()
{
	if (UseSound != nullptr)
	{
		AudioComponent->PostAkEvent(UseSound, int32(0), FOnAkPostEventCallback());
	}
}
