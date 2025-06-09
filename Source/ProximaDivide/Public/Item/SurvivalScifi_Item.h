// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "SurvivalScifi_Item.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASurvivalScifi_Item : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASurvivalScifi_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* Collider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UItemDataAsset* DataAsset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;

	UFUNCTION()
	virtual UMaterialInterface* GetMaterial() { return nullptr; }

	UFUNCTION()
	virtual void SetMaterial(UMaterialInterface* Material) { }

	UFUNCTION()
	virtual void SetOverlayMaterial(UMaterialInterface* Material) { }

	UFUNCTION(BlueprintPure)
	virtual UMeshComponent* GetMesh() { return nullptr; }

	UFUNCTION()
	UBoxComponent* GetCollider() { return Collider; }

	UFUNCTION()
	FVector GetBoxExtent();

	UFUNCTION()
	virtual void UpdateRelatives() {}
};
