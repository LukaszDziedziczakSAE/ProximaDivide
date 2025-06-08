// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/AmbienceAndMusic.h"
#include "AkGameplayStatics.h"
#include "AkAudioEvent.h"

// Sets default values
AAmbienceAndMusic::AAmbienceAndMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmbienceAndMusic::BeginPlay()
{
	Super::BeginPlay();

	if (AmbienceState != nullptr && Ambience != nullptr)
	{
		UAkGameplayStatics::SetState(AmbienceState);
		UAkGameplayStatics::PostEvent(Ambience, nullptr, int32(0), FOnAkPostEventCallback(), false);
	}
	if (Music != nullptr) UAkGameplayStatics::PostEvent(Music, nullptr, int32(0), FOnAkPostEventCallback(), false);
}

// Called every frame
void AAmbienceAndMusic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

