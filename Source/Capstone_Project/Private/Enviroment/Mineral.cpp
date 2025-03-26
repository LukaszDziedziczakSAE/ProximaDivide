// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Mineral.h"

// Sets default values
AMineral::AMineral()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AMineral::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMineral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMineral::IsSucessfulHit()
{
	float random = FMath::RandRange(0.0f, 1.0f);
	return random <= SpawnProbability;
}