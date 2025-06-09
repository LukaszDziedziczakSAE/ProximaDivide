// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Character/SurvivalSciFi_Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROXIMADIVIDE_API APlayerCharacter : public ASurvivalSciFi_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UOxygenComponent* OxygenComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UExhaustionComponent* ExhaustionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USustenanceComponent* SustenanceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerInteractionComponent* PlayerInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerTutorialComponent* TutorialComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* FPS_Arms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAkAudioEvent* HelmetLightSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	UCameraComponent* GetCameraComponent() { return CameraComponent; }

	UFUNCTION(BlueprintPure)
	UOxygenComponent* GetOxygenComponent() { return OxygenComponent; }

	UFUNCTION(BlueprintPure)
	UExhaustionComponent* GetExhaustionComponent() { return ExhaustionComponent; }

	UFUNCTION(BlueprintPure)
	USustenanceComponent* GetSustenanceComponent() { return SustenanceComponent; }

	UFUNCTION(BlueprintPure)
	UPlayerInteractionComponent* GetPlayerInteractionComponent() { return PlayerInteractionComponent; }
	
	UFUNCTION(BlueprintPure)
	UPlayerTutorialComponent* GetTutorialComponent() { return TutorialComponent; }

	UFUNCTION()
	void Interact();

	virtual void SpawnHandItems() override;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetFPS_Arms() { return FPS_Arms; }

	virtual float PlayMontage(UAnimMontage* Montage) override;

	UFUNCTION(BlueprintPure)
	class ASurvivalScifi_HUD* GetHUD();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsInside = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bStatsLoaded;

	virtual void ChangeStat(EStat StatType, float Amount) override;

	virtual void DropFromInventory(UItemDataAsset* DataAsset, FIntPoint Position) override;

	virtual void DropFromPaperdoll(UItemDataAsset* DataAsset, int SlotNumber) override;

	virtual bool TryPickUpItem(class UItemDataAsset* Item, bool bShowNotification = true) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsControlable = true;

	UFUNCTION()
	bool HelemetLightOn();

	UFUNCTION()
	void ToggleHelmetLight();

	UFUNCTION()
	struct FPlayerData GetSaveData();

	UFUNCTION()
	void LoadDataFromSave();

	virtual void Footstep() override;
};
