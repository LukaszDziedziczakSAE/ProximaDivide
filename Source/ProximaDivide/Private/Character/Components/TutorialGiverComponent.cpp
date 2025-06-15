// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Components/TutorialGiverComponent.h"
#include "AkAudioEvent.h"
#include "AkComponent.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerTutorialComponent.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "AI/Astronaut_AIController.h"
#include "Animation/SurvivalScifi_AnimInstance.h"
#include "AkGameplayStatics.h"
#include "Enviroment/FlightDeckChair.h"
#include "Components/CapsuleComponent.h"

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

	if (Player->GetTutorialComponent() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing tutorial component in player character"));
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

	if (FlightDeckChair != nullptr)
	{
		FlightDeckChair->HideCharacter();
	}

	PrepTutorial();
}

void UTutorialGiverComponent::OnPartStart()
{
	if (Index < 0 && Index >= TutorialParts.Num()) return;

	if (TutorialParts[Index].TutorialAudio != nullptr)
	{
		if (UseVoiceComponent) CharacterVoice->PostAkEvent(TutorialParts[Index].TutorialAudio, int32(AkCallbackType::AK_EndOfEvent), PostEventCallback);

		else if (UseEvent) TutorialParts[Index].TutorialAudio->PostOnComponent(CharacterVoice, PostEventCallback, int32(AkCallbackType::AK_EndOfEvent), true);

		else UAkGameplayStatics::PostEvent(TutorialParts[Index].TutorialAudio, Player, int32(AkCallbackType::AK_EndOfEvent), PostEventCallback, true);

		if (AnimInstance != nullptr) AnimInstance->StartTalking();

		AudioIndex = Index;
	}
	ObjectivePrecomplete = false;

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

	if (GetCurrentPart().ShowInventoryInfo)
	{
		Player->GetTutorialComponent()->ShowInventoryInfo = true;
		Player->GetHUD()->UpdateTutorialInfo();
	}

	if (GetCurrentPart().ShowSlotInfo)
	{
		Player->GetTutorialComponent()->ShowSlotInfo = true;
		Player->GetHUD()->UpdateTutorialInfo();
	}

	if (GetCurrentPart().ShowPlayerStats)
	{
		Player->GetTutorialComponent()->HideStats = false;
		Player->GetHUD()->ShowGameHUD();
	}

	if (GetCurrentPart().ShowActionBar)
	{
		Player->GetTutorialComponent()->HideActionBar = false;
		Player->GetHUD()->ShowGameHUD();
	}

	if (GetCurrentPart().ShowDayTime)
	{
		Player->GetTutorialComponent()->HideDayTime = false;
		Player->GetHUD()->ShowGameHUD();
	}

	if (GetCurrentPart().AllowLook)
	{
		Player->GetTutorialComponent()->PreventLook = false;
	}

	if (GetCurrentPart().AllowMovement)
	{
		Player->GetTutorialComponent()->PreventMovement = false;
	}

	if (GetCurrentPart().AllowInteract)
	{
		Player->GetTutorialComponent()->PreventInteract = false;
	}

	if (GetCurrentPart().AllowActionBarUse)
	{
		Player->GetTutorialComponent()->PreventActionBarUse = false;
	}

	if (GetCurrentPart().AllowInventoryOpen)
	{
		Player->GetTutorialComponent()->PreventInventoryOpen = false;
	}
}

void UTutorialGiverComponent::OnSitComplete()
{
	if (FlightDeckChair != nullptr)
	{
		FlightDeckChair->ShowCharacter();
	}

	GetOwner()->Destroy();
}

// Called every frame
void UTutorialGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bMoveTowardsChair)
	{
		if (SitDownDelay > 0) SitDownDelay -= DeltaTime;

		if (SitDownDelay <= 0)
		{
			FVector Location = GetOwner()->GetActorLocation();
			FVector Direction = FlightDeckChair->CharacterLocation() - Location;
			Direction.Normalize();
			Location = Location + (Direction * MoveSpeed * DeltaTime);
			GetOwner()->SetActorLocation(Location);
		}
	}
}

void UTutorialGiverComponent::PlaybackComplete(EAkCallbackType CallbackType, UAkCallbackInfo* CallbackInfo)
{
	if (AudioIndex == Index) AudioIndex = -1;

	StopTalkingAnimation();

	if (GetCurrentPart().TutorialCondition == OnAudioFinish || ObjectivePrecomplete)
	{
		GoToNextPart();
	}

	//UE_LOG(LogTemp, Warning, TEXT("Tutorial Audio Complete"));
}

void UTutorialGiverComponent::GoToNextPart()
{
	if (AudioIndex != -1)
	{
		ObjectivePrecomplete = true;
		//UE_LOG(LogTemp, Log, TEXT("Objective precomplete"));
		return;
	}

	//UE_LOG(LogTemp, Log, TEXT("Starting next tutorial part"));
	if (Index < 0) Index = 0;
	else Index++;

	if (Index >= TutorialParts.Num())
	{
		CompleteTutorial();
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

void UTutorialGiverComponent::PrepTutorial()
{
    if (TutorialParts.Num() == 0) return;
    if (Player == nullptr) return;

    UPlayerTutorialComponent* TutorialComp = Player->GetTutorialComponent();
	if (TutorialComp != nullptr)
	{
		TutorialComp->HideActionBar = true;
		TutorialComp->HideStats = true;
		TutorialComp->HideDayTime = true;

		TutorialComp->PreventLook = true;
		TutorialComp->PreventMovement = true;
		TutorialComp->PreventInteract = true;
		TutorialComp->PreventActionBarUse = true;
		TutorialComp->PreventInventoryOpen = true;
	}

	if (IsValid(Player->GetHUD())) Player->GetHUD()->ShowGameHUD();
}

void UTutorialGiverComponent::BeginTutorial()
{
	if (TutorialParts.Num() > 0)
	{
		GoToNextPart();
		if (AI != nullptr) AI->UpdateBB();
		UE_LOG(LogTemp, Log, TEXT("Tutorial Starting..."));
	}
}

void UTutorialGiverComponent::CompleteTutorial()
{
	Index = -1;
	HasCompleted = true;
	if (AI != nullptr) AI->UpdateBB();
	Player->GetTutorialComponent()->HideActionBar = false;
	Player->GetTutorialComponent()->HideStats = false;
	Player->GetTutorialComponent()->HideDayTime = false;
	Player->GetTutorialComponent()->PreventLook = false;
	Player->GetTutorialComponent()->PreventMovement = false;
	Player->GetTutorialComponent()->PreventInteract = false;
	Player->GetTutorialComponent()->PreventActionBarUse = false;
	Player->GetTutorialComponent()->PreventInventoryOpen = false;
	Player->GetHUD()->ShowGameHUD();
	UE_LOG(LogTemp, Log, TEXT("Tutorial Complete"));

	if (PostTutorialMission != nullptr)
	{
		Player->AddNewMission(PostTutorialMission);
	}
}

void UTutorialGiverComponent::PlaySitDownAnimation()
{
	if (SitDownMontage == nullptr) return;

	ASurvivalSciFi_Character* Character = GetOwner<ASurvivalSciFi_Character>();

	float t = Character->PlayMontage(SitDownMontage);
	t *= SitDownCompletePercentage;

	FTimerHandle  UseTimer;
	GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &UTutorialGiverComponent::OnSitComplete, t, false);

	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bMoveTowardsChair = true;

	SitDownMontage = nullptr;
}

void UTutorialGiverComponent::StopTalkingAnimation()
{
	if (AnimInstance != nullptr) AnimInstance->StopTalking();
}

