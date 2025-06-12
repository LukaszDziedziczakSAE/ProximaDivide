// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Container.generated.h"

UENUM(BlueprintType)
enum class EContainerState : uint8
{
	Closed UMETA(DisplayName = "Closed"),
	Open UMETA(DisplayName = "Open"),
	Opening UMETA(DisplayName = "Opening"),
	Closing UMETA(DisplayName = "Closing")
};

UCLASS()
class PROXIMADIVIDE_API AContainer : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Lid;

	UPROPERTY(EditAnywhere)
	FVector OpenPosition;

	UPROPERTY(VisibleAnywhere)
	FVector ClosedPosition;

	UPROPERTY(EditAnywhere)
	FRotator OpenRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator ClosedRotation;

	UPROPERTY(EditAnywhere)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere)
	EContainerState ContainerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid ContainerID;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	UFUNCTION(BlueprintPure)
	FGuid GetContainerID() const { return ContainerID; }

	UFUNCTION(BlueprintCallable)
	struct FContainerSaveData GetContainerSaveData() const;

	UFUNCTION(BlueprintCallable)
	void LoadContainerSaveData(const FContainerSaveData& Data);

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;
};
