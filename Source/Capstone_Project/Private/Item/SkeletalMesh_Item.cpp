// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/SkeletalMesh_Item.h"
#include "Components/BoxComponent.h"

ASkeletalMesh_Item::ASkeletalMesh_Item()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Collider->SetupAttachment(Mesh);

	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Mesh->SetEnableGravity(true);
	Mesh->SetSimulatePhysics(true);
}

void ASkeletalMesh_Item::SetMaterial(UMaterialInterface* Material)
{
	Mesh->SetMaterial(0, Material);
}

void ASkeletalMesh_Item::SetOverlayMaterial(UMaterialInterface* Material)
{
	Mesh->SetOverlayMaterial(Material);
}
