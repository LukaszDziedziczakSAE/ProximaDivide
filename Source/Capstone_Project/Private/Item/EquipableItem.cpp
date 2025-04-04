// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableItem.h"
#include "Character/SurvivalSciFi_Character.h"
#include "AkGameplayStatics.h"
#include "AkComponent.h"
#include "AkAudioEvent.h"


AEquipableItem::AEquipableItem()
{
	AkComponent = CreateDefaultSubobject<UAkComponent>(TEXT("AkComponent"));
}

void AEquipableItem::BeginPlay()
{
	Super::BeginPlay();

	//EquipSoundID = PlayWiseEvent(EquipSound, true);

	//FOnAkPostEventCallback nullCallback;
	//UAkGameplayStatics::PostEvent(EquipSound, this, 0, nullCallback);

	//EquipSound->
	//AkComponent->PostAkEvent(EquipSound);
	// 
	//if (EquipSound != nullptr)
	//{
	//	if (!EquipSound->IsLoaded()) EquipSound->LoadData();
	//	//EquipSound->PostOnActor(this, FOnAkPostEventCallback(), 0, true);
	//	FOnAkPostEventCallback nullCallback;
	//	EquipSoundID = UAkGameplayStatics::PostEvent(EquipSound, this, 0, nullCallback);
	//	UE_LOG(LogTemp, Log, TEXT("Wwise Event Playing %d"), EquipSoundID);
	//}
	
}

int32 AEquipableItem::PlayWiseEvent(UAkAudioEvent* Event, bool bStopWhenAttachedToDestoryed)
{
	int PlayingID = AK_INVALID_PLAYING_ID;

	if (Event)
	{
		FOnAkPostEventCallback nullCalback;
		PlayingID = UAkGameplayStatics::PostEvent(Event, this, int32(0), nullCalback, bStopWhenAttachedToDestoryed);
		UE_LOG(LogTemp, Log, TEXT("Wwise Event: %s Playing"), *Event->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wwise Event reference on EquipableItem is invalid"));
	}

	return PlayingID;
}

void AEquipableItem::UpdateRelatives()
{
	SetActorRelativeLocation(RelativeLocation);
	SetActorRelativeRotation(RelativeRotation);
}

void AEquipableItem::Use()
{
	if (Busy) return;

	if (UseMontage != nullptr)
	{
		//float t = GetOwner<ASurvivalSciFi_Character>()->PlayAnimMontage(UseMontage);
		float t = GetOwner<ASurvivalSciFi_Character>()->PlayMontage(UseMontage);
		Busy = true;

		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &AEquipableItem::UseFinish, t * PercentageBusy, false);
	}

	OnStartUsing.Broadcast();
}

void AEquipableItem::UseFinish()
{
	Busy = false;
	if (GetOwner<ASurvivalSciFi_Character>()->GetUseItemDown()) Use();

	OnEndUsing.Broadcast();
}
