// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/FlightDeckChair.h"
#include "Character/Player/PlayerCharacter.h"
#include "AkGameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "LevelSequencePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "LevelSequenceActor.h"

// Sets default values
AFlightDeckChair::AFlightDeckChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Chair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chair"));
	SetRootComponent(Chair);

	Chair->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AFlightDeckChair::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USurvivalSciFi_GameInstance>(GetGameInstance());
}

void AFlightDeckChair::OnLevelSeqenceComplete()
{
	UE_LOG(LogTemp, Log, TEXT("Fligh deck chair OnLevelSeqenceComplete call"));

	if (GameInstance != nullptr)
	{
		if (GameInstance->GetCurrentSaveGame() != nullptr)
		{
			GameInstance->GetCurrentSaveGame()->Enviroment = PostSequenceEnviroment;
		}
		else UE_LOG(LogTemp, Error, TEXT("Fligh deck chair cannot get current save game"));

		UE_LOG(LogTemp, Log, TEXT("Fligh deck chair OnLevelSeqenceComplete SwitchToMap call"));
		GameInstance->SwitchToMap(NewMapName, PlayerStartTag);
		UE_LOG(LogTemp, Log, TEXT("Fligh deck chair OnLevelSeqenceComplete SwitchToMap complete"));
	}

	else UE_LOG(LogTemp, Error, TEXT("Fligh deck chair cannot find Game Instance"));
}

// Called every frame
void AFlightDeckChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlightDeckChair::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!bInteractable) return;


	Player = PlayerCharacter;
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

			//if (GameInstance != nullptr) GameInstance->SetEnviroment(SequenceEnviroment);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to create level sequence player"));
		}
	}
}

FString AFlightDeckChair::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (!bInteractable) return TEXT("");
	return TEXT("Sit Down");
}

void AFlightDeckChair::ShowCharacter()
{
	if (Character == nullptr) return;
	Character->SetActorHiddenInGame(false);
}

void AFlightDeckChair::HideCharacter()
{
	if (Character == nullptr) return;
	Character->SetActorHiddenInGame(true);
}

FVector AFlightDeckChair::CharacterLocation()
{
	if (Character == nullptr) return FVector::Zero();
	return Character->GetActorLocation() + CharacterOffset;
}

