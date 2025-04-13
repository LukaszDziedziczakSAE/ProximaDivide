// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/EquipableSkItem.h"
#include "FirearmSk.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API AFirearmSk : public AEquipableSkItem
{
	GENERATED_BODY()

public:
	AFirearmSk();

protected:
	UPROPERTY(EditDefaultsOnly)
	float Range{ 5000.0f };

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed{ 5000.0f };

	UFUNCTION()
	void SpawnImpact();

	UPROPERTY(VisibleAnywhere)
	FHitResult Hit;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* Impact;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* FireMontage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawn;
	
public:
	virtual void Use() override;
};
