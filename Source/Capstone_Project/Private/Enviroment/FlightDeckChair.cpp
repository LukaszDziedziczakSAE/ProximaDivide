// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/FlightDeckChair.h"
#include "Character/PlayerCharacter.h"
#include "AkGameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "LevelSequencePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SurvivalScifi_HUD.h"

// Sets default values
AFlightDeckChair::AFlightDeckChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Chair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chair"));
	SetRootComponent(Chair);

	Chair->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	PlayerPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Player Position"));
	PlayerPosition->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFlightDeckChair::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlightDeckChair::OnLevelSeqenceComplete()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("L_Mars"));
	//PlayerCharacter->GetHUD()->SequenceEnd();
}

// Called every frame
void AFlightDeckChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlightDeckChair::Interact(APlayerCharacter* PlayerCharacter)
{
	if (LevelSequence != nullptr)
	{
		ALevelSequenceActor* SeqenceActor = nullptr;
		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), SeqenceActor);

		if (LevelSequencePlayer)
		{
			PlayerCharacter->IsControlable = false;
			PlayerCharacter->GetHUD()->SequenceStart();

			LevelSequencePlayer->OnFinished.AddDynamic(this, &AFlightDeckChair::OnLevelSeqenceComplete);
			LevelSequencePlayer->Play();

			if (SeqenceState != nullptr) UAkGameplayStatics::SetState(SeqenceState);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to create level sequence player"));
		}
	}
}

FString AFlightDeckChair::InteractionText()
{
	return TEXT("Sit Down");
}