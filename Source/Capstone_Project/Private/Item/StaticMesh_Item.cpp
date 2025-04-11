// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/StaticMesh_Item.h"
#include "Components/BoxComponent.h"

AStaticMesh_Item::AStaticMesh_Item()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Collider->SetupAttachment(Mesh);

	Mesh->SetEnableGravity(true);
	Mesh->SetSimulatePhysics(true);
}

void AStaticMesh_Item::SetMaterial(UMaterialInterface* Material)
{
	Mesh->SetMaterial(0, Material);
}

void AStaticMesh_Item::SetOverlayMaterial(UMaterialInterface* Material)
{
	Mesh->SetOverlayMaterial(Material);
}
