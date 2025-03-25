// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/MineralExtractorComponent.h"
#include "Item/EquipableItem.h"
#include "Components/BoxComponent.h"
#include "Enviroment/Mineral.h"

// Sets default values for this component's properties
UMineralExtractorComponent::UMineralExtractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMineralExtractorComponent::BeginPlay()
{
	Super::BeginPlay();

	AEquipableItem* EquipableItem = GetOwner<AEquipableItem>();

	Collider = EquipableItem->GetCollider();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &UMineralExtractorComponent::OnColliderBeginOverlap);

	EquipableItem->OnStartUsing.AddDynamic(this, &UMineralExtractorComponent::ActivateExtraction);
	EquipableItem->OnEndUsing.AddDynamic(this, &UMineralExtractorComponent::DeactivateExtraction);
}

void UMineralExtractorComponent::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Active) return;

	AMineral* Mineral = Cast<AMineral>(OtherActor);
	if (Mineral == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("Hit Mineral"));
	DeactivateExtraction();
}

void UMineralExtractorComponent::ActivateExtraction()
{
	Active = true;
}

void UMineralExtractorComponent::DeactivateExtraction()
{
	Active = false;
}


// Called every frame
void UMineralExtractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

