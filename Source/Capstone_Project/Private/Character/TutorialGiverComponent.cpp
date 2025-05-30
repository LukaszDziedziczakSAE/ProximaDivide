// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/TutorialGiverComponent.h"
#include "AkAudioEvent.h"
#include "AkComponent.h"
#include "Character/SurvivalSciFi_Character.h"

// Sets default values for this component's properties
UTutorialGiverComponent::UTutorialGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorialGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterVoice = Cast<ASurvivalSciFi_Character>(GetOwner())->GetVoiceComponent();
	if (CharacterVoice == nullptr) return;

	PostEventCallback = FOnAkPostEventCallback();
	static FName FunctionName("StopCallback");
	PostEventCallback.BindUFunction(this, FunctionName);

	if (TutorialAudio.Num() > 0)
	{
		Index = 0;
		CharacterVoice->PostAkEvent(TutorialAudio[Index], int32(0), PostEventCallback);

		/*FLatentActionInfo Info;
		Info.CallbackTarget = GetOwner();
		Info.ExecutionFunction = "OnTutorialAudioComplete";
		CharacterVoice->PostAkEventAndWaitForEnd(TutorialAudio[Index], Info);*/
	}
	
}

void UTutorialGiverComponent::OnTutorialAudioComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Tutorial Audio Complete"));
}

// Called every frame
void UTutorialGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialGiverComponent::StopCallback(EAkCallbackType CallbackType, UAkCallbackInfo* CallbackInfo)
{
	OnTutorialAudioComplete();
}

