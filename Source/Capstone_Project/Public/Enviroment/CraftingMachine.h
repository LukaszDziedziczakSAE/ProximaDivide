// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "CraftingMachine.generated.h"

UENUM(BlueprintType)
enum class ECraftingMachineState : uint8
{
	Closed UMETA(DisplayName = "Closed"),
	Opening UMETA(DisplayName = "Opening"),
	Closing UMETA(DisplayName = "Closing"),
	Standby UMETA(DisplayName = "Standby"),
	Crafting UMETA(DisplayName = "Crafting")
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText() override;

	UFUNCTION()
	TArray<class URecipeDataAsset*> GetRecipes() { return Recipes; }

	UFUNCTION()
	float GetProgress();
};
