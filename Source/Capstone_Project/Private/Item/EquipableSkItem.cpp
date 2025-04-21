// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableSkItem.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"
#include "Components/BoxComponent.h"
#include "Character/SurvivalSciFi_Character.h"
#include "NiagaraComponent.h"

AEquipableSkItem::AEquipableSkItem()
{
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Collider->SetBoxExtent(FVector(0, 0, 0));
	Collider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	UseVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Use VFX"));
	UseVFX->SetupAttachment(Mesh);
	UseVFX->bAutoActivate = false;
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

void AEquipableSkItem::Use()
{
	if (Busy) return;

	if (UseMontage != nullptr)
	{
		float t = GetOwner<ASurvivalSciFi_Character>()->PlayMontage(UseMontage);
		Busy = true;
		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &AEquipableSkItem::UseFinish, t * PercentageBusy, false);

		if (UseVFX->GetAsset() != nullptr) UseVFX->ActivateSystem();

		OnStartUsing.Broadcast();
	}
}

void AEquipableSkItem::UseFinish()
{
	Busy = false;
	if (Repeating && GetOwner<ASurvivalSciFi_Character>()->GetUseItemDown()) Use();

	OnEndUsing.Broadcast();
}

void AEquipableSkItem::PlayEquipSound()
{
	if (EquipSound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing EquipSound reference"));
		return;
	}
	EquipSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}

void AEquipableSkItem::PlayUnequipSound()
{
	if (UnequipSound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing UnequipSound reference"));
		return;
	}
	UnequipSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}

void AEquipableSkItem::PlayUseSound()
{
	if (UseSound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing UseSound reference"));
		return;
	}
	UseSound->PostAtLocation(GetActorLocation(), GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
}