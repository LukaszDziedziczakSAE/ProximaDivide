// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/StaticMesh_Item.h"
#include "EquipableItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartUsingSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndUsingSignature);

UCLASS()
class CAPSTONE_PROJECT_API AEquipableItem : public AStaticMesh_Item
{
	GENERATED_BODY()

public:
	AEquipableItem();

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
	

	UPROPERTY(BlueprintAssignable)
	FOnStartUsingSignature OnStartUsing;

	UPROPERTY(BlueprintAssignable)
	FOnEndUsingSignature OnEndUsing;

	virtual void UpdateRelatives() override;
	
	UFUNCTION()
	virtual void Use();

	UFUNCTION()
	virtual void UseFinish();

	UFUNCTION()
	UAnimMontage* GetUseMontage() { return UseMontage; }

	UFUNCTION(BlueprintCallable)
	void PlayEquipSound();

	UFUNCTION(BlueprintCallable)
	void PlayUseSound();

	UFUNCTION(BlueprintPure)
	UAkAudioEvent* GetHitSound() { return HitSound; }

	UFUNCTION()
	void TurnOnColliderOverlap();

	UFUNCTION()
	void TurnOffColliderOverlap();
};
