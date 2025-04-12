// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
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
class CAPSTONE_PROJECT_API AContainer : public AActor, public IInteraction
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText() override;
};
