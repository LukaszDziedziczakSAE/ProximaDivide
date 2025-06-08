// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/AmbientSoundActor.h"
#include "AkComponent.h"

// Sets default values
AAmbientSoundActor::AAmbientSoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAmbientSoundActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (AudioComponent != nullptr && AmbientSound != nullptr)
		AudioComponent->PostAkEvent(AmbientSound, int32(0), FOnAkPostEventCallback());
}

// Called every frame
void AAmbientSoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

