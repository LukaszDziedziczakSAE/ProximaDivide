// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Container.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Game/SurvivalScifi_PlayerController.h"
#include "InputActionValue.h"
#include "Game/SurvivalScifi_SaveGame.h"

// Sets default values
AContainer::AContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SetRootComponent(Body);

	Lid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid"));
	Lid->SetupAttachment(Body);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));

	Body->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	Lid->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	if (!ContainerID.IsValid())
	{
	    ContainerID = FGuid::NewGuid();
	}
}

// Called when the game starts or when spawned
void AContainer::BeginPlay()
{
	Super::BeginPlay();
	
	ClosedPosition = Lid->GetRelativeLocation();
	ClosedRotation = Lid->GetRelativeRotation();
}

// Called every frame
void AContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AContainer::Interact(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->GetController<ASurvivalScifi_PlayerController>()->ToggleInventory(FInputActionValue());
	ContainerState = EContainerState::Open;
}

FString AContainer::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (ContainerState == EContainerState::Closed) return TEXT("Open Container");
	else return TEXT("");
}

FContainerSaveData AContainer::GetContainerSaveData() const
{
    FContainerSaveData Data;
    Data.ContainerID = ContainerID;
    if (InventoryComponent)
    {
        Data.InventoryItems = InventoryComponent->GetItems();
    }
    return Data;
}

void AContainer::LoadContainerSaveData(const FContainerSaveData& Data)
{
    if (ContainerID == Data.ContainerID && InventoryComponent != nullptr)
    {
        InventoryComponent->SetItems(Data.InventoryItems);
    }
}

