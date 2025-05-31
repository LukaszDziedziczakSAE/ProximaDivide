// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/TutorialGiverComponent.h"
#include "AkAudioEvent.h"
#include "AkComponent.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Character/PlayerCharacter.h"
#include "Character/PlayerTutorialComponent.h"
#include "UI/SurvivalScifi_HUD.h"
#include "AI/Astronaut_AIController.h"
#include "Animation/SurvivalScifi_AnimInstance.h"

UTutorialGiverComponent::UTutorialGiverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTutorialGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UObject*> Players;
	GetObjectsOfClass(APlayerCharacter::StaticClass(), Players);
	if (Players.Num() > 0)
		Player = Cast<APlayerCharacter>(Players[0]);

	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing player reference in tutorial giver"));
		return;
	}

	Player->GetTutorialComponent()->TutorialGiver = this;

	CharacterVoice = Cast<ASurvivalSciFi_Character>(GetOwner())->GetVoiceComponent();
	if (CharacterVoice == nullptr) return;

	static FName FunctionName("PlaybackComplete");
	PostEventCallback.BindUFunction(this, FunctionName);

	AnimInstance = Cast<USurvivalScifi_AnimInstance>(Cast<ASurvivalSciFi_Character>(GetOwner())->GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr) 
		UE_LOG(LogTemp, Error, TEXT("Missing AnimInstance reference in tutorial giver"));
}

void UTutorialGiverComponent::OnPartStart()
{
	if (Index < 0 && Index >= TutorialParts.Num()) return;

	if (TutorialParts[Index].TutorialAudio != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Playing %s"), *TutorialParts[Index].TutorialAudio->GetWwiseName().ToString());
		TutorialParts[Index].TutorialAudio->PostOnComponent(CharacterVoice, PostEventCallback, int32(AkCallbackType::AK_EndOfEvent), true);
		if (AnimInstance != nullptr) AnimInstance->StartTalking();
	}

	if (Player == nullptr) return;

	if (GetCurrentPart().ShowMouseMoveInfo)
	{
		Player->GetTutorialComponent()->ShowMouseMoveInfo = true;
		Player->GetHUD()->UpdateTutorialInfo();
	}

	if (GetCurrentPart().ShowMovementInfo)
	{
		Player->GetTutorialComponent()->ShowMovementInfo = true;
		Player->GetHUD()->UpdateTutorialInfo();
	}


}

// Called every frame
void UTutorialGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialGiverComponent::PlaybackComplete(EAkCallbackType CallbackType, UAkCallbackInfo* CallbackInfo)
{
	if (AnimInstance != nullptr) AnimInstance->StopTalking();

	if (GetCurrentPart().TutorialCondition == OnAudioFinish)
	{
		GoToNextPart();
	}

	//UE_LOG(LogTemp, Warning, TEXT("Tutorial Audio Complete"));
}

void UTutorialGiverComponent::GoToNextPart()
{
	if (Index < 0) Index = 0;
	else Index++;

	if (Index >= TutorialParts.Num())
	{
		Index = -1;
		HasCompleted = true;
		if (AI != nullptr) AI->UpdateBB();
		UE_LOG(LogTemp, Warning, TEXT("Tutorial Complete"));
		return;
	}

	if (Index >= 0 && Index < TutorialParts.Num())
		OnPartStart();
}

FTutorialPart UTutorialGiverComponent::GetCurrentPart()
{
	if (Index >= 0 && Index < TutorialParts.Num())
	{
		return TutorialParts[Index];
	}

	return FTutorialPart();
}

void UTutorialGiverComponent::BeginTutorial()
{
	if (HasCompleted) return;
	if (TutorialParts.Num() > 0)
	{
		GoToNextPart();
	}

	if (AI != nullptr) AI->UpdateBB();
}

