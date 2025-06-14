// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Interface/Repair.h"
#include "Generator.generated.h"

UCLASS()
class PROXIMADIVIDE_API AGenerator : public AActor, public IInteraction, public IRepair
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UMaintenanceComponent* MaintenanceComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* RepairInteractionZone;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Inherited via IInteraction
	void Interact(APlayerCharacter* PlayerCharacter) override;

	FString InteractionText(APlayerCharacter* PlayerCharacter) override;


	// Inherited via IRepair
	UMaintenanceComponent* GetMaintenanceComponent() const override;

	UBoxComponent* GetRepairInteractionZone() const override;


	// Inherited via IRepair
	void Repair(APlayerCharacter* PlayerCharacter) const override;

};
