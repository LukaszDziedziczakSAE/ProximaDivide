// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Generator.h"
#include "Item/MaintenanceComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	MaintenanceComponent = CreateDefaultSubobject<UMaintenanceComponent>(TEXT("Maintenance Component"));

	RepairInteractionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Repair Interaction Zone"));
	RepairInteractionZone->SetupAttachment(Root);
	RepairInteractionZone->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	RepairInteractionZone->ComponentTags.Add(FName("RepairZone"));
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenerator::Interact(APlayerCharacter* PlayerCharacter)
{

}

FString AGenerator::InteractionText(APlayerCharacter* PlayerCharacter)
{
	return FString();
}

UMaintenanceComponent* AGenerator::GetMaintenanceComponent() const
{
	return MaintenanceComponent;
}

UBoxComponent* AGenerator::GetRepairInteractionZone() const
{
	return RepairInteractionZone;
}

void AGenerator::Repair(APlayerCharacter* PlayerCharacter) const
{
	if (MaintenanceComponent != nullptr) MaintenanceComponent->Repair(PlayerCharacter);
}

