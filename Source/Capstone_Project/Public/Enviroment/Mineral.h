// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mineral.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API AMineral : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMineral();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// items that is extracted from this node
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UItemDataAsset* DataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnProbability{ 1.0 }; // as a percentage

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool IsSucessfulHit();

	UFUNCTION()
	UItemDataAsset* GetDataAsset() { return DataAsset; }
};
