// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/SurvivalScifi_Item.h"
#include "Item/ItemDataAsset.h"
#include "Components/BoxComponent.h"
#include "Character/PlayerCharacter.h"
#include "UI/SurvivalScifi_HUD.h"

// Sets default values
ASurvivalScifi_Item::ASurvivalScifi_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	Collider->SetupAttachment(GetRootComponent());

	Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	AudioComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Audio Component"));
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

FString ASurvivalScifi_Item::InteractionText()
{
	return TEXT("Pick Up ") + DataAsset->Name;
}

FVector ASurvivalScifi_Item::GetBoxExtent()
{
	return Collider->GetScaledBoxExtent();
}

