// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Item/RecipeDataAsset.h"
#include "CraftingMachine.generated.h"

UENUM(BlueprintType)
enum class ECraftingMachineState : uint8
{
	Closed UMETA(DisplayName = "Closed"),
	Opening UMETA(DisplayName = "Opening"),
	Closing UMETA(DisplayName = "Closing"),
	Standby UMETA(DisplayName = "Standby"),
	Crafting UMETA(DisplayName = "Crafting"),
	Finishing UMETA(DisplayName = "Finishing")
};

UCLASS()
class CAPSTONE_PROJECT_API ACraftingMachine : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACraftingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Machine;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* InteractionCollider;

	UPROPERTY(EditAnywhere)
	TArray<class URecipeDataAsset*> Recipes;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Tray;

	UPROPERTY(EditAnywhere)
	float OpenAngle;

	UPROPERTY(VisibleAnywhere)
	float ClosedAngle;

	UPROPERTY(EditAnywhere)
	float OpenCloseTime;

	UPROPERTY(VisibleAnywhere)
	float Timer;

	UPROPERTY(EditAnywhere)
	USceneComponent* CraftingItemPosition;

	UPROPERTY(VisibleAnywhere)
	ECraftingMachineState CraftingMachineState;

	UFUNCTION()
	void OpeningTick(float DeltaTime);

	UFUNCTION()
	void ClosingTick(float DeltaTime);

	UFUNCTION()
	void CraftingTick(float DeltaTime);

	UFUNCTION()
	void FinishingTick(float DeltaTime);

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* CraftingLaser;

	UPROPERTY(VisibleAnywhere)
	URecipeDataAsset* CurrentlyCrafting;

	UPROPERTY(VisibleAnywhere)
	class ASurvivalScifi_Item* CurrentlyCraftingItem;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* CraftingMaterialPrefab;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* CraftingMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* CurrentlyCraftingItemMaterial;

	UFUNCTION()
	float GetLaserHeight();

	UFUNCTION()
	FVector GetLaserPosition(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float LaserMovementSpeed{ 100.0f };

	UPROPERTY()
	FVector CurrentLaserPoint;

	UPROPERTY()
	FVector TargetLaserPoint;

	UFUNCTION()
	void SetNextTargetLaserPoint();

	UPROPERTY(EditAnywhere)
	float PostCraftingPause{ 2.5f };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText() override;

	UFUNCTION()
	TArray<class URecipeDataAsset*> GetRecipes() { return Recipes; }

	UFUNCTION()
	TArray<URecipeDataAsset*> GetRecipesByType(ECraftingMenuType CraftingMenuType);

	UFUNCTION()
	float GetProgress();

	UFUNCTION()
	void Craft(URecipeDataAsset* Recipe);

	UFUNCTION()
	ECraftingMachineState GetCraftingMachineState() { return CraftingMachineState; }
	
	UFUNCTION()
	URecipeDataAsset* GetCurrentlyCrafting(){ return CurrentlyCrafting; }

	UFUNCTION()
	FText CraftingStatusText();
};
