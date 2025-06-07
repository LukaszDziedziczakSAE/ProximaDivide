// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Moxie.h"
#include "Character/OxygenComponent.h"
#include "Character/PlayerCharacter.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"

// Sets default values
AMoxie::AMoxie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	AudioComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMoxie::BeginPlay()
{
	Super::BeginPlay();

	Stored = Capacity;

	if (AudioComponent != nullptr && AmbientSound != nullptr)
		AudioComponent->PostAkEvent(AmbientSound, int32(0), FOnAkPostEventCallback());
}

// Called every frame
void AMoxie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Stored < Capacity)
	{
		Stored = FMath::Clamp(Stored + (RechargeRate * DeltaTime), 0, Capacity);
	}

	if (CooldownTimer > 0) CooldownTimer -= DeltaTime;
}

void AMoxie::Interact(APlayerCharacter* PlayerCharacter)
{
	if (CooldownTimer > 0) return;

	UE_LOG(LogTemp, Warning, TEXT("Moxie Interaction. Missing: %f, Stored: %f"), PlayerCharacter->GetOxygenComponent()->GetMissingValue(), Stored);

	float RefillAmount = FMath::Min(PlayerCharacter->GetOxygenComponent()->GetMissingValue(), Stored);

	if (RefillAmount > 0)
	{
		Stored -= RefillAmount;
		PlayerCharacter->GetOxygenComponent()->ModifyValue(RefillAmount);

		// play sound
		if (MoxieUseSound != nullptr)
			MoxieUseSound->PostOnActor(PlayerCharacter, FOnAkPostEventCallback(), int32(0), true);

		// update UI ???

		UE_LOG(LogTemp, Log, TEXT("Refilled Oxygen %f"), RefillAmount);

		CooldownTimer = Cooldown;
	}
}

FString AMoxie::InteractionText()
{
	if (CooldownTimer > 0) return TEXT("");
	return TEXT("Extract Oxygen");
}

