// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerSuitVoiceComponent.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "AkGameplayStatics.h"
#include "AkAudioEvent.h"
#include "Character/Player/PlayerCharacter.h"

// Sets default values for this component's properties
UPlayerSuitVoiceComponent::UPlayerSuitVoiceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerSuitVoiceComponent::BeginPlay()
{
	Super::BeginPlay();

	static FName FunctionName("PlaybackComplete");
	PostEventCallback.BindUFunction(this, FunctionName);

	Player = GetOwner<APlayerCharacter>();

	USurvivalSciFi_GameInstance* GI = Cast<USurvivalSciFi_GameInstance>(GetWorld()->GetGameInstance());
	if (GI != nullptr)
	{
		GI->GetCurrentSaveGame();
		USurvivalScifi_SaveGame* SaveGame = GI->GetCurrentSaveGame();

		if (SaveGame != nullptr)
		{
			for (FBeginPlayEvent BPE : BeginPlayEvents)
			{
				if (BPE.MapName == SaveGame->CurrentLevelName &&
					BPE.PlayerStartTag == SaveGame->PlayerStartTag)
				{
					Play(BPE.AkAudioEvent, true);
				}
			}
		}
	}
	
}


void UPlayerSuitVoiceComponent::PlaybackComplete()
{
	bIsPlaying = false;
	bPreventQueue = false;
}

// Called every frame
void UPlayerSuitVoiceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayQueue.Num() > 0 && !bIsPlaying)
	{
		UAkAudioEvent* AkAudioEvent = PlayQueue[0];
		PlayQueue.RemoveAt(0);

		UAkGameplayStatics::PostEvent(AkAudioEvent, Player, int32(AkCallbackType::AK_EndOfEvent), PostEventCallback, true);

		bIsPlaying = true;
	}
}

void UPlayerSuitVoiceComponent::Play(UAkAudioEvent* AkAudioEvent, bool PreventQueue)
{
	if (bPreventQueue || AkAudioEvent == nullptr || PlayQueue.Contains(AkAudioEvent)) return;
	bPreventQueue = PreventQueue;
	PlayQueue.Add(AkAudioEvent);
}

