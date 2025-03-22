// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalSciFi_Character.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API ASurvivalSciFi_Character : public ACharacter
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AEquipableItem* RightHandItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool UseItemDown;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	UFUNCTION(BlueprintPure)
	UPaperdollComponent* GetPaperdollComponent() { return PaperdollComponent; }

	UFUNCTION(BlueprintCallable)
	void SetMovementSpeed(bool IsRunning);

	UFUNCTION(BlueprintCallable)
	bool TryPickUpItem(class UItemDataAsset* Item);

	UFUNCTION()
	void SelectSlot(int SlotNumber);

	UFUNCTION()
	virtual void SpawnRightHand();

	UFUNCTION()
	void DespawnRightHand();

	UFUNCTION()
	void UseItem();

	UFUNCTION()
	void UseItemRepeating();

	UFUNCTION()
	void UseItemEnd();

	UFUNCTION()
	virtual float PlayMontage(UAnimMontage* Montage);

	UFUNCTION(BlueprintPure)
	bool GetUseItemDown() { return UseItemDown; }
};
