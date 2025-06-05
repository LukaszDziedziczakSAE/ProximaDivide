// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Moxie.h"
#include "Character/OxygenComponent.h"
#include "Character/PlayerCharacter.h"

// Sets default values
AMoxie::AMoxie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AMoxie::BeginPlay()
{
	Super::BeginPlay();

	Stored = Capacity;
}

// Called every frame
void AMoxie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Stored < Capacity)
	{
		Stored = FMath::Clamp(Stored + (RechargeRate * DeltaTime), 0, Capacity);
	}
}

void AMoxie::Interact(APlayerCharacter* PlayerCharacter)
{
	float RefillAmount = FMath::Min(PlayerCharacter->GetOxygenComponent()->GetMissingValue(), Stored);

	if (RefillAmount > 0)
	{
		Stored -= RefillAmount;
		PlayerCharacter->GetOxygenComponent()->ModifyValue(RefillAmount);

		// play sound
		// update UI
	}
}

FString AMoxie::InteractionText()
{
	return TEXT("Extract Oxygen");
}

