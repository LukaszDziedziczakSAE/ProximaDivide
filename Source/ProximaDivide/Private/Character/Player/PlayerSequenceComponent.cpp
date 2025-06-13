// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerSequenceComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "LevelSequencePlayer.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"

// Sets default values for this component's properties
UPlayerSequenceComponent::UPlayerSequenceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerSequenceComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<APlayerCharacter>();

	USurvivalSciFi_GameInstance* GI = Cast<USurvivalSciFi_GameInstance>(GetWorld()->GetGameInstance());
	if (GI != nullptr)
	{
		GI->GetCurrentSaveGame();
		USurvivalScifi_SaveGame* SaveGame = GI->GetCurrentSaveGame();

		if (SaveGame != nullptr && !SaveGame->bIsExitSave)
		{
			for (FBeginPlaySequence BPS : BeginPlaySequences)
			{
				if (BPS.MapName == SaveGame->CurrentLevelName &&
					BPS.PlayerStartTag == SaveGame->PlayerStartTag)
				{
					PlayLevelSequence(BPS.LevelSequence);
				}
			}
		}
	}
}

// Called every frame
void UPlayerSequenceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerSequenceComponent::PlayLevelSequence(class ULevelSequence* LevelSequence)
{
	if (LevelSequence == nullptr || Player == nullptr) return;

	ALevelSequenceActor* SeqenceActor = nullptr;
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), SeqenceActor);

	if (LevelSequencePlayer)
	{
		Player->IsControlable = false;
		bIsPlayingSequence = true;

		ASurvivalScifi_HUD* HUD = Player->GetHUD();
		if (HUD)
		{
			HUD->HideGameHUD();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayLevelSequence: Player HUD is null, cannot hide game HUD."));
		}

		Player->SetActorHiddenInGame(true);

		LevelSequencePlayer->OnFinished.AddDynamic(this, &UPlayerSequenceComponent::OnLevelSeqenceComplete);
		LevelSequencePlayer->Play();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to create level sequence player"));
	}
}

void UPlayerSequenceComponent::OnLevelSeqenceComplete()
{
	Player->SetActorHiddenInGame(false);
	bIsPlayingSequence = false;
	Player->IsControlable = true;

	ASurvivalScifi_HUD* HUD = Player->GetHUD();
	if (HUD)
	{
		HUD->ShowGameHUD();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnLevelSeqenceComplete: Player HUD is null, cannot show game HUD."));
	}
}