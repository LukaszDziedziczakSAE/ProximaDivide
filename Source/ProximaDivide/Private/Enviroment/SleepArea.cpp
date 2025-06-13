// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/SleepArea.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Notifications/ObjectiveMarker_UserWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Components/ExhaustionComponent.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "LevelSequencePlayer.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "GameFramework/PlayerStart.h"

// Sets default values
ASleepArea::ASleepArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SetRootComponent(Area);
	Area->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Area->SetEnableGravity(false);
	Area->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	ObjectiveMarkerComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ObjectiveMarkerComponent"));
	ObjectiveMarkerComponent->SetupAttachment(RootComponent);
	ObjectiveMarkerComponent->SetWidgetSpace(EWidgetSpace::Screen);
	ObjectiveMarkerComponent->SetVisibility(false); // Start hidden
}

// Called when the game starts or when spawned
void ASleepArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASleepArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASleepArea::Interact(APlayerCharacter* PlayerCharacter)
{
	Player = PlayerCharacter;
	if (!CanPlayerSleep(PlayerCharacter)) return;

	if (LevelSequence != nullptr)
	{
		ALevelSequenceActor* SeqenceActor = nullptr;
		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), SeqenceActor);

		if (LevelSequencePlayer)
		{
			PlayerCharacter->IsControlable = false;
			PlayerCharacter->GetHUD()->HideGameHUD();

			CurrentHoursToSleep = HoursToSleep(PlayerCharacter);

			LevelSequencePlayer->OnFinished.AddDynamic(this, &ASleepArea::OnLevelSeqenceComplete);
			Player->GetHUD()->SequenceStart();
			LevelSequencePlayer->Play();

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to create level sequence player"));
		}
	}

	else
	{
		GetGameInstance<USurvivalSciFi_GameInstance>()->StartWakeFromSleep(CurrentHoursToSleep, GetPlayerStartTag());
		CurrentHoursToSleep = -1;
	}
}

FString ASleepArea::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (!CanPlayerSleep(PlayerCharacter)) return TEXT("");
	return TEXT("go to Sleep");
}

bool ASleepArea::CanPlayerSleep(APlayerCharacter* PlayerCharacter)
{
	return PlayerCharacter->GetExhaustionComponent()->GetPercentage() >= MinExhaustionPercentage;
}

int ASleepArea::HoursToSleep(APlayerCharacter* PlayerCharacter)
{
	return FMath::CeilToInt(PlayerCharacter->GetExhaustionComponent()->GetPercentage() * MaxHoursToSleep);
}

void ASleepArea::ShowObjectiveMarker()
{
	if (ObjectiveMarkerComponent)
	{
		if (ObjectiveMarkerComponent->GetWidgetClass() != ObjectiveMarkerWidgetClass)
		{
			ObjectiveMarkerComponent->SetWidgetClass(ObjectiveMarkerWidgetClass);
			ObjectiveMarkerComponent->InitWidget();
		}

		if (UObjectiveMarker_UserWidget* Widget = Cast<UObjectiveMarker_UserWidget>(ObjectiveMarkerComponent->GetUserWidgetObject()))
		{
			Widget->SetMarkerText(MarkerText);
			Widget->Owner = ObjectiveMarkerComponent;
			Widget->Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
		}
		ObjectiveMarkerComponent->SetVisibility(true);
	}
}

void ASleepArea::HideObjectiveMarker()
{
	if (ObjectiveMarkerComponent)
	{
		ObjectiveMarkerComponent->SetVisibility(false);
		ObjectiveMarkerComponent->DestroyComponent();
		ObjectiveMarkerComponent = nullptr;
	}
}

FName ASleepArea::GetPlayerStartTag()
{
	if (PlayerStart == nullptr ) return FName();
	return PlayerStart->PlayerStartTag;
}

void ASleepArea::OnLevelSeqenceComplete()
{
	if (Player == nullptr) return;

	Player->GetExhaustionComponent()->SetValue(0);
	Player->GetHUD()->ShowBlackscreen();
	GetGameInstance<USurvivalSciFi_GameInstance>()->StartWakeFromSleep(CurrentHoursToSleep, GetPlayerStartTag());
	CurrentHoursToSleep = -1;
}

