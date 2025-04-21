// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/SkeletalMesh_Item.h"
#include "Character/EStat.h"
#include "EquipableSkItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartUsingItemSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndUsingItemSignature);

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

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* UseVFX;

	UPROPERTY(EditDefaultsOnly)
	EStat ChangeStat;

	UPROPERTY(EditDefaultsOnly)
	float ChangeAmount;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnStartUsingItemSignature OnStartUsing;

	UPROPERTY(BlueprintAssignable)
	FOnEndUsingItemSignature OnEndUsing;

	virtual void UpdateRelatives() override;

	UFUNCTION()
	virtual void Use();

	UFUNCTION()
	virtual void UseFinish();


	UFUNCTION(BlueprintCallable)
	void PlayEquipSound();

	UFUNCTION(BlueprintCallable)
	void PlayUnequipSound();

	UFUNCTION(BlueprintCallable)
	void PlayUseSound();

	UFUNCTION(BlueprintPure)
	EStat GetChangeStatType() { return ChangeStat; }

	UFUNCTION(BlueprintPure)
	float GetChangeStatAmount() { return ChangeAmount; }
};
