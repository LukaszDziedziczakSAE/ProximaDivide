// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/SurvivalScifi_Item.h"
#include "SkeletalMesh_Item.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API ASkeletalMesh_Item : public ASurvivalScifi_Item
{
	GENERATED_BODY()

public:
	ASkeletalMesh_Item();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

public:
	virtual UMaterialInterface* GetMaterial() override { return Mesh->GetMaterial(0); }

	void SetMaterial(UMaterialInterface* Material) override;

	void SetOverlayMaterial(UMaterialInterface* Material) override;

	virtual UMeshComponent* GetMesh() override { return Mesh; }

	
};
