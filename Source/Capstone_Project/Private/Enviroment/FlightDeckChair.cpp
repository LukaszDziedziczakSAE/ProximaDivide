// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/FlightDeckChair.h"
#include "Character/PlayerCharacter.h"
#include "AkGameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "LevelSequencePlayer.h"
#include "Kismet/GameplayStatics.h"

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
}

// Called every frame
void AFlightDeckChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlightDeckChair::Interact(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->IsControlable = false;

	//Chair->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//FVector Location = PlayerPosition->GetComponentLocation();
	////Location.Z = PlayerCharacter->GetActorLocation().Z;

	//FRotator Rotation = PlayerPosition->GetComponentRotation();
	//FRotator CameraRotation = PlayerCharacter->GetCameraComponent()->GetComponentRotation();
	//CameraRotation.Yaw = Rotation.Yaw;

	//PlayerCharacter->SetActorLocationAndRotation(Location, Rotation);
	////PlayerCharacter->GetCameraComponent()->SetWorldRotation(Rotation);

	if (MusicChange != nullptr)
		UAkGameplayStatics::PostEvent(MusicChange, nullptr, int32(0), FOnAkPostEventCallback());

	if (LevelSequence != nullptr)
	{
		ALevelSequenceActor* SeqenceActor = nullptr;
		// Create a level sequence player
		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), SeqenceActor);

		// Check if the player was created successfully
		if (LevelSequencePlayer)
		{
			// Play the level sequence
			LevelSequencePlayer->OnFinished.AddDynamic(this, &AFlightDeckChair::OnLevelSeqenceComplete);
			LevelSequencePlayer->Play();
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