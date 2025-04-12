// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/MineralExtractorComponent.h"
#include "Item/EquipableItem.h"
#include "Components/BoxComponent.h"
#include "Enviroment/Mineral.h"
#include "Character/PlayerCharacter.h"
#include "Item/InventoryComponent.h"
#include "UI/SurvivalScifi_HUD.h"
#include "AkAudioEvent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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

	EquipableItem = GetOwner<AEquipableItem>();

	Collider = EquipableItem->GetCollider();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &UMineralExtractorComponent::OnColliderBeginOverlap);

	EquipableItem->OnStartUsing.AddDynamic(this, &UMineralExtractorComponent::ResetHits);
	//EquipableItem->OnEndUsing.AddDynamic(this, &UMineralExtractorComponent::DeactivateExtraction);

	Inventory = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->GetInventoryComponent();

	if (Inventory == nullptr) UE_LOG(LogTemp, Error, TEXT("Missing inventory ref"));

	ResetHits();
}

void UMineralExtractorComponent::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Inventory == nullptr || OtherActor == nullptr) return;

	if (HitActors.Contains(OtherActor)) return;
	HitActors.Add(OtherActor);

	//UE_LOG(LogTemp, Warning, TEXT("Hit %s at %s"), *OtherActor->GetName(), *SweepResult.ImpactPoint.ToString());

	AMineral* Mineral = Cast<AMineral>(OtherActor);
	if (Mineral != nullptr && Mineral->GetDataAsset() != nullptr)
	{
		if (Mineral->IsSucessfulHit())
			Inventory->TryAddItem(Mineral->GetDataAsset());


	}

	if (EquipableItem->GetHitSound() != nullptr)
		EquipableItem->GetHitSound()->PostAtLocation(
			EquipableItem->GetActorLocation(),
			EquipableItem->GetActorRotation(),
			FOnAkPostEventCallback(),
			int32(0),
			GetWorld()
		);

	if (Impact != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Impact, EquipableItem->GetActorLocation(), EquipableItem->GetOwner()->GetActorRotation());
	}
}

void UMineralExtractorComponent::ResetHits()
{
	HitActors.Empty();
	HitActors.Add(EquipableItem->GetOwner());
}


// Called every frame
void UMineralExtractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

