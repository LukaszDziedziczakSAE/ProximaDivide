// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Door/AirlockSwitch.h"
#include "Enviroment/Door/Airlock.h"
#include "AkGameplayStatics.h"

void AAirlockSwitch::BeginPlay()
{
	Super::BeginPlay();


	Airlock = Cast<AAirlock>(GetParentActor());
	if (Airlock == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Switch missing airlock ref"));
}

void AAirlockSwitch::Interact(APlayerCharacter* PlayerCharacter)
{
	if (Airlock == nullptr) return;

	switch (AirlockSwitchSide)
	{
	case EAirlockSwitchSide::InsideInner:
		Airlock->InsideInnerSwitchPress();
		break;

	case EAirlockSwitchSide::InsideOuter:
		Airlock->InsideOuterSwitchPress();
		break;

	case EAirlockSwitchSide::Outer:
		Airlock->OuterSwitchPress();
		break;

	case EAirlockSwitchSide::Inner:
		Airlock->InnerSwitchPress();
		break;
	}

	UAkGameplayStatics::PostEvent(SwitchActivatedSound, this, int32(0), FOnAkPostEventCallback(), false);
}

FString AAirlockSwitch::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (Airlock == nullptr) return TEXT("");

	switch (AirlockSwitchSide)
	{
	case EAirlockSwitchSide::InsideInner:
		if (Airlock->GetAirlockState() == EAirlockState::OpenIn)
			return TEXT("Open Airlock Door");
		else if (Airlock->GetAirlockState() == EAirlockState::OpenOut)
			return TEXT("Cycle Airlock");
		else return TEXT("");

	case EAirlockSwitchSide::InsideOuter:
		if (Airlock->GetAirlockState() == EAirlockState::OpenOut)
			return TEXT("Open Airlock Door");
		else if (Airlock->GetAirlockState() == EAirlockState::OpenIn)
			return TEXT("Cycle Airlock");
		else return TEXT("");

	case EAirlockSwitchSide::Outer:
		if (Airlock->GetAirlockState() == EAirlockState::OpenOut)
			return TEXT("Open Airlock Door");
		else if (Airlock->GetAirlockState() == EAirlockState::OpenIn)
			return TEXT("Cycle Airlock");
		else return TEXT("");

	case EAirlockSwitchSide::Inner:
		if (Airlock->GetAirlockState() == EAirlockState::OpenIn)
			return TEXT("Open Airlock Door");
		else if (Airlock->GetAirlockState() == EAirlockState::OpenOut)
			return TEXT("Cycle Airlock");
		else return TEXT("");

	default: return TEXT("");
	}
}
