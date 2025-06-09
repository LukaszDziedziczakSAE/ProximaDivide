// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/EStat.h"
#include "SurvivalSciFi_Character.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASurvivalSciFi_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASurvivalSciFi_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPaperdollComponent* PaperdollComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WalkingSpeed{ 200.0f };

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RunningSpeed{ 500.0f };

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float JumpForce{ 100.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASurvivalScifi_Item* RightHandItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASurvivalScifi_Item* LeftHandItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool UseItemDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps")
	class UAkAudioEvent* FootstepEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps")
	class UAkSwitchValue* DirtValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps")
	UAkSwitchValue* InteriorValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps")
	UAkSwitchValue* MetalValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector DropSpawnOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DeathTimer = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkComponent* VoiceComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	UFUNCTION(BlueprintPure)
	UHealthComponent* GetHealthComponent() { return HealthComponent; }

	UFUNCTION(BlueprintPure)
	UPaperdollComponent* GetPaperdollComponent() { return PaperdollComponent; }

	UFUNCTION(BlueprintCallable)
	void SetMovementSpeed(bool IsRunning);

	UFUNCTION(BlueprintCallable)
	virtual bool TryPickUpItem(class UItemDataAsset* Item, bool bShowNotification = true);

	UFUNCTION()
	void SelectSlot(int SlotNumber);

	UFUNCTION()
	virtual void SpawnHandItems();

	UFUNCTION()
	void DespawnHandItems();

	UFUNCTION()
	void UseItem();

	UFUNCTION()
	void UseItemRepeating();

	UFUNCTION()
	void UseItemEnd();

	UFUNCTION()
	void SingleUseItemEnd();

	UFUNCTION()
	virtual float PlayMontage(UAnimMontage* Montage);

	UFUNCTION(BlueprintPure)
	bool GetUseItemDown() { return UseItemDown; }

	UFUNCTION(BlueprintCallable)
	virtual void Footstep();

	UFUNCTION(BlueprintPure)
	ASurvivalScifi_Item* GetRightHandItem() { return RightHandItem; }

	UFUNCTION(BlueprintPure)
	ASurvivalScifi_Item* GetLeftHandItem() { return LeftHandItem; }

	UFUNCTION()
	virtual void ChangeStat(EStat StatType, float Amount);

	UFUNCTION()
	virtual void DropFromInventory(UItemDataAsset* DataAsset, FIntPoint Position);

	UFUNCTION()
	virtual void DropFromPaperdoll(UItemDataAsset* DataAsset, int SlotNumber);

	UFUNCTION(BlueprintPure)
	bool IsAlive();

	UFUNCTION()
	UAkComponent* GetVoiceComponent() { return VoiceComponent; }
};
