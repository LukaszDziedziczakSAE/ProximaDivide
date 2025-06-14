// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalScifi_PlayerController.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASurvivalScifi_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUIOnlyMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Run;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Slot1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Slot2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Slot3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Slot4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Slot5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Use;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_InventorySelect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_InventoryAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Pause;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_SkipTutorial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Light;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Info;

	UPROPERTY(VisibleAnywhere)
	bool bIsSprinting;

	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	bool AllowLook();
	
	UFUNCTION()
	bool AllowMove();

	UFUNCTION()
	bool AllowInteraction();

	UFUNCTION()
	bool AllowOpenMenu();

	UFUNCTION()
	void RunStart();

	UFUNCTION()
	void RunEnd();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Slot1();

	UFUNCTION()
	void Slot2();

	UFUNCTION()
	void Slot3();

	UFUNCTION()
	void Slot4();

	UFUNCTION()
	void Slot5();

	UFUNCTION()
	void UseItem();

	UFUNCTION()
	void UseItemEnd();

	UFUNCTION()
	void Jump();

	UFUNCTION()
	bool CharacterAlive();

	UFUNCTION()
	void OnPlayerDeath(AActor* DestroyedActor);

	UFUNCTION()
	void SkipTutorial();

	UFUNCTION()
	void ToggleLight();

	UFUNCTION()
	void ResetPlayer();

	UPROPERTY()
	bool bIsPlayerResetting;

	UFUNCTION()
	void ToggleInfo(); // mission info

	UFUNCTION()
	void CloseAnyMenu();

	UFUNCTION()
	bool IsShowingAnyMenu();

public:
	UFUNCTION()
	void ToggleInventory(const FInputActionValue& Value);
	
	UFUNCTION()
	void PauseToggle();

	UFUNCTION(BlueprintPure)
	APlayerCharacter* GetPlayerCharacter() { return PlayerCharacter; }
};
