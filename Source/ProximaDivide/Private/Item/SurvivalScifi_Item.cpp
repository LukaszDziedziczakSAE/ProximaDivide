// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/SurvivalScifi_Item.h"
#include "Item/Crafting/ItemDataAsset.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"

// Sets default values
ASurvivalScifi_Item::ASurvivalScifi_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	Collider->SetupAttachment(GetRootComponent());

	Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	// Generate a new GUID for this item if not already set
	if (!ItemID.IsValid())
	{
		ItemID = FGuid::NewGuid();
	}
}

// Called when the game starts or when spawned
void ASurvivalScifi_Item::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASurvivalScifi_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASurvivalScifi_Item::Interact(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter->TryPickUpItem(DataAsset))
	{
		Destroy();
	}
}

FString ASurvivalScifi_Item::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (DataAsset == nullptr) return TEXT("");
	return TEXT("Pick Up ") + DataAsset->Name;
}

FVector ASurvivalScifi_Item::GetBoxExtent()
{
	return Collider->GetScaledBoxExtent();
}

