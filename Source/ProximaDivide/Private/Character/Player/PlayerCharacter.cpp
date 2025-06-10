// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/Components/HealthComponent.h"
#include "Character/Components/OxygenComponent.h"
#include "Character/Components/ExhaustionComponent.h"
#include "Character/Components/SustenanceComponent.h"
#include "Character/Player/PlayerInteractionComponent.h"
#include "Character/Player/PlayerTutorialComponent.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Character/Components/PaperdollComponent.h"
#include "Item/Equipment/EquipableItem.h"
#include "Item/Equipment/EquipableItemDataAsset.h"
#include "AkGameplayStatics.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Game/SurvivalSciFi_GameInstance.h"
#include "Game/SurvivalScifi_SaveGame.h"
#include "Components/SpotLightComponent.h"
#include "AkAudioEvent.h"
#include "Character/Player/PlayerObjectivesComponent.h"
#include "Game/MissionDataAsset.h"
#include "Game/SurvivalScifiGameMode.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	OxygenComponent = CreateDefaultSubobject<UOxygenComponent>(TEXT("Oxygen"));

	ExhaustionComponent = CreateDefaultSubobject<UExhaustionComponent>(TEXT("Exhaustion"));

	SustenanceComponent = CreateDefaultSubobject<USustenanceComponent>(TEXT("Sustenance"));

	PlayerInteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("Player Interaction Component"));

	TutorialComponent = CreateDefaultSubobject<UPlayerTutorialComponent>(TEXT("Tutorial Component"));

	FPS_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	FPS_Arms->SetupAttachment(CameraComponent);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	SpotLight->SetupAttachment(CameraComponent);

	ObjectivesComponent = CreateDefaultSubobject<UPlayerObjectivesComponent>(TEXT("Objectives"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpotLight->SetHiddenInGame(true);
	LoadDataFromSave();

	ASurvivalScifiGameMode* GameMode = Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		UMissionDataAsset* Mission = GameMode->GetOnStartMission();
		if (Mission != nullptr) AddNewMission(Mission);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsAlive() && GetController<APlayerController>() != nullptr && GetHUD() != nullptr && !GetHUD()->IsShowingDeathScreen())
	{
		GetHUD()->HideInventory();
		GetHUD()->HideCraftingMenuOnly();
		GetHUD()->HideGameHUD();
		GetHUD()->HideInteraction();
		GetHUD()->ShowDeathScreen();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Interact()
{
	PlayerInteractionComponent->Interact();
}

void APlayerCharacter::SpawnHandItems()
{
	if (!PaperdollComponent->IsCurrentSlotHaveItem()) return;

	DespawnHandItems();

	if (PaperdollComponent->GetCurrentSlot().Item->RightHand != nullptr)
	{
		RightHandItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(PaperdollComponent->GetCurrentSlot().Item->RightHand);
		RightHandItem->AttachToComponent(FPS_Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHand"));
		RightHandItem->SetOwner(this);
		RightHandItem->UpdateRelatives();
	}

	if (PaperdollComponent->GetCurrentSlot().Item->LeftHand != nullptr)
	{
		LeftHandItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(PaperdollComponent->GetCurrentSlot().Item->LeftHand);
		LeftHandItem->AttachToComponent(FPS_Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeftHand"));
		LeftHandItem->SetOwner(this);
		LeftHandItem->UpdateRelatives();
	}
}

float APlayerCharacter::PlayMontage(UAnimMontage* Montage)
{
	return FPS_Arms->GetAnimInstance()->Montage_Play(Montage);
}

ASurvivalScifi_HUD* APlayerCharacter::GetHUD()
{
	return GetController<APlayerController>()->GetHUD<ASurvivalScifi_HUD>();;
}

void APlayerCharacter::ChangeStat(EStat StatType, float Amount)
{
	switch(StatType)
	{
	case EStat::Oxygen:
		OxygenComponent->ModifyValue(Amount);
		break;

	case EStat::Health:
		HealthComponent->ModifyValue(Amount);
		break;

	case EStat::Sustenance:
		SustenanceComponent->ModifyValue(Amount);
		break;

	case EStat::Exhaustion:
		ExhaustionComponent->ModifyValue(Amount);
		break;
	}
}

void APlayerCharacter::DropFromInventory(UItemDataAsset* DataAsset, FIntPoint Position)
{
	if (InventoryComponent->TryRemoveItemAt(DataAsset, Position))
	{
		AActor* Item = GetWorld()->SpawnActor(DataAsset->ItemClass);
		Item->SetActorLocation(CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * 50));
	}
}

void APlayerCharacter::DropFromPaperdoll(UItemDataAsset* DataAsset, int SlotNumber)
{
	if (PaperdollComponent->TryRemoveItemFromSlot(SlotNumber))
	{
		AActor* Item = GetWorld()->SpawnActor(DataAsset->ItemClass);
		Item->SetActorLocation(CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * 50));
	}
}

bool APlayerCharacter::TryPickUpItem(UItemDataAsset* Item, bool bShowNotification)
{
	UEquipableItemDataAsset* Equipable = Cast<UEquipableItemDataAsset>(Item);
	if (Equipable != nullptr && PaperdollComponent->TryAddEquipable(Equipable))
	{
		TutorialComponent->ItemAddedToSlot();
		return true;
	}

	if (InventoryComponent->TryAddItem(Item, bShowNotification))
	{
		TutorialComponent->ItemPickedUp();
		return true;
	}

	return false;
}

bool APlayerCharacter::HelemetLightOn()
{
	return !SpotLight->bHiddenInGame;
}

void APlayerCharacter::ToggleHelmetLight()
{
	if (SpotLight != nullptr) SpotLight->SetHiddenInGame(!SpotLight->bHiddenInGame);
	if (HelmetLightSound != nullptr) HelmetLightSound->PostOnActor(this , FOnAkPostEventCallback(), int32(0), true);
	if (!SpotLight->bHiddenInGame) TutorialComponent->HasTurnOnLight();
}

FPlayerData APlayerCharacter::GetSaveData()
{
	FPlayerData Stats = FPlayerData();
	Stats.Health = HealthComponent->GetCurrentValue();
	Stats.Oxygen = OxygenComponent->GetCurrentValue();
	Stats.Sustenance = SustenanceComponent->GetCurrentValue();
	Stats.Exhaustion = ExhaustionComponent->GetCurrentValue();
	return Stats;
}

FObjectivesData APlayerCharacter::GetObjectiveSaveData()
{
	return ObjectivesComponent->GetSaveData();
}

void APlayerCharacter::LoadDataFromSave()
{
	USurvivalSciFi_GameInstance* GameInstance = GetGameInstance<USurvivalSciFi_GameInstance>();
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player could not GetGameInstance"));
		return;
	}

	USurvivalScifi_SaveGame* Save = GameInstance->GetCurrentSaveGame();
	if (Save != nullptr)
	{
		bIsInside = (Save->Enviroment == EEnviroment::Inside 
			|| Save->Enviroment == EEnviroment::Ship);

		FPlayerData Stats = Save->PlayerData;

		HealthComponent->SetValue(Stats.Health);
		OxygenComponent->SetValue(Stats.Oxygen);
		SustenanceComponent->SetValue(Stats.Sustenance);
		ExhaustionComponent->SetValue(Stats.Exhaustion);

		ObjectivesComponent->LoadDataFromSave(Save->ObjectivesData);

		bStatsLoaded = true;
	}

	else UE_LOG(LogTemp, Error, TEXT("No save data on Player load"));
}

void APlayerCharacter::Footstep()
{
	Super::Footstep();

	ExhaustionComponent->Footstep();
}

void APlayerCharacter::AddNewMission(class UMissionDataAsset* MissionDataAsset)
{
	if (ObjectivesComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNewMission failed: ObjectivesComponent is null"));
		return;
	}
	if (MissionDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("APlayerCharacter::AddNewMission received null MissionDataAsset"));
		return;
	}

	ObjectivesComponent->AddNewMission(MissionDataAsset);
}

