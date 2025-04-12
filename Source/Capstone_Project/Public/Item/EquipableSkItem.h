// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/SkeletalMesh_Item.h"
#include "EquipableSkItem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_PROJECT_API AEquipableSkItem : public ASkeletalMesh_Item
{
	GENERATED_BODY()

public:
	AEquipableSkItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FVector RelativeLocation;

	UPROPERTY(EditDefaultsOnly)
	FQuat RelativeRotation;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* UseMontage;

	UPROPERTY(EditDefaultsOnly)
	float PercentageBusy{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	bool Repeating;

	UPROPERTY(VisibleAnywhere)
	bool Busy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* EquipSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* UnequipSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* UseSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* HitSound;
	
public:
	virtual void UpdateRelatives() override;

	UFUNCTION(BlueprintCallable)
	void PlayEquipSound();

	UFUNCTION(BlueprintCallable)
	void PlayUnequipSound();

	UFUNCTION(BlueprintCallable)
	void PlayUseSound();
};
