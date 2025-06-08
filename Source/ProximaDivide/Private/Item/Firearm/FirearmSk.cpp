// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/Firearm/FirearmSk.h"
#include "Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "AkAudioEvent.h"
#include "Item/Firearm/Projectile.h"
#include "Kismet/KismetMathLibrary.h"

AFirearmSk::AFirearmSk()
{
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectil Spawn"));
	ProjectileSpawn->SetupAttachment(Mesh);
}

void AFirearmSk::SpawnImpact()
{
	if (Impact != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Impact, Hit.ImpactPoint, GetOwner()->GetActorRotation());
	}

	if (HitSound != nullptr)
	{
		HitSound->PostAtLocation(Hit.ImpactPoint, GetActorRotation(), FOnAkPostEventCallback(), int32(0), GetWorld());
	}
}

void AFirearmSk::Use()
{

	if (Busy || UseMontage == nullptr) return;

	FVector Start = GetOwner<APlayerCharacter>()->GetCameraComponent()->GetComponentLocation();
	FVector End = Start + (GetOwner<APlayerCharacter>()->GetCameraComponent()->GetForwardVector() * Range);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
	float Distance = FVector::Distance(GetActorLocation(), Hit.ImpactPoint);

	if (Hit.bBlockingHit)
	{
		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &AFirearmSk::SpawnImpact, Distance / ProjectileSpeed, false);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Firearm did not hit"));

	if (Mesh->GetAnimInstance() != nullptr && FireMontage != nullptr)
		Mesh->GetAnimInstance()->Montage_Play(FireMontage);
	
	if (ProjectileClass != nullptr)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass);
		Projectile->Set(ProjectileSpeed, Distance);
		Projectile->SetActorLocation(ProjectileSpawn->GetComponentLocation());
		Projectile->SetActorRotation(
			UKismetMathLibrary::FindLookAtRotation(ProjectileSpawn->GetComponentLocation(), Hit.ImpactPoint));
	}

	Super::Use();
}
