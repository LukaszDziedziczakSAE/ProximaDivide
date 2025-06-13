// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Shower.h"
#include "Particles/ParticleSystemComponent.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"
#include "Components/BoxComponent.h"

// Sets default values
AShower::AShower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	Collider->SetupAttachment(GetRootComponent());

	Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Effect"));
	ParticleEffect->SetupAttachment(Mesh);

	ParticleEffect->bAutoActivate = false; // Start with the particle effect deactivated

	AudioComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AShower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShower::Interact(APlayerCharacter* PlayerCharacter)
{
	if (bIsOn)
	{
		if (ParticleEffect) ParticleEffect->DeactivateSystem();

		if (AudioComponent && AmbientSoundOff)
			AudioComponent->PostAkEvent(AmbientSoundOff);

		bIsOn = false;
	}
	else
	{
		if (ParticleEffect) ParticleEffect->ActivateSystem();

		if (AudioComponent && AmbientSoundOn)
			AudioComponent->PostAkEvent(AmbientSoundOn);

		bIsOn = true;
	}
}


FString AShower::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (bIsOn)
	{
		return TEXT("Turn off the Shower");
	}
	else
	{
		return TEXT("Turn on the Shower");
	}
}

