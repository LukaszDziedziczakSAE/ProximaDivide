// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UDroneScanningComponent* DroneScanningComponent;

	UPROPERTY(EditAnywhere)
	class UDroneMovementComponent* DroneMovementComponent;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ScanningEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	UDroneScanningComponent* GetDroneScanningComponent() { return DroneScanningComponent; }

	UFUNCTION(BlueprintPure)
	UNiagaraComponent* GetScanningEffect() { return ScanningEffect; }

	UFUNCTION()
	UStaticMeshComponent* GetMesh() { return Mesh; }
};
