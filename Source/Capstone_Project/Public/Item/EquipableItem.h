// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/SurvivalScifi_Item.h"
#include "EquipableItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartUsingSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndUsingSignature);

UCLASS()
class CAPSTONE_PROJECT_API AEquipableItem : public ASurvivalScifi_Item
{
	GENERATED_BODY()

public:
	AEquipableItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UAkComponent* AkComponent;

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

	UFUNCTION()
	int32 PlayWiseEvent(UAkAudioEvent* Event, bool bStopWhenAttachedToDestoryed);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* EquipSound;
	int32 EquipSoundID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* UnequipSound;
	int32 UnequipSoundID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* UseSound;
	int32 UseSoundID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* StrikeSound;
	int32 StrikeSoundID;

	UPROPERTY(BlueprintAssignable)
	FOnStartUsingSignature OnStartUsing;

	UPROPERTY(BlueprintAssignable)
	FOnEndUsingSignature OnEndUsing;


	UFUNCTION()
	void UpdateRelatives();
	
	UFUNCTION()
	virtual void Use();

	UFUNCTION()
	virtual void UseFinish();

	UFUNCTION()
	UAnimMontage* GetUseMontage() { return UseMontage; }

};
