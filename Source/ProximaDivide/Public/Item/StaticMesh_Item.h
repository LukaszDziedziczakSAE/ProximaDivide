// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Item/SurvivalScifi_Item.h"
#include "StaticMesh_Item.generated.h"

UCLASS()
class PROXIMADIVIDE_API AStaticMesh_Item : public ASurvivalScifi_Item
{
	GENERATED_BODY()

public:
	AStaticMesh_Item();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

public:
	virtual UMaterialInterface* GetMaterial() override { return Mesh->GetMaterial(0); }

	void SetMaterial(UMaterialInterface* Material) override;

	void SetOverlayMaterial(UMaterialInterface* Material) override;

	virtual UMeshComponent* GetMesh() override { return Mesh; }
	
};
