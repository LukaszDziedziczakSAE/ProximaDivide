// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Switch.h"
#include "Components/BoxComponent.h"
#include "Interface/SwitchActivated.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitch::Interact(APlayerCharacter* PlayerCharacter)
{
	ISwitchActivated* Interface = Cast<ISwitchActivated>(Activatee);
	if (Interface == nullptr) return;
	Interface->SwitchActivation();
}

FString ASwitch::InteractionText()
{
	ISwitchActivated* Interface = Cast<ISwitchActivated>(Activatee);
	if (Interface == nullptr) return TEXT("");
	return Interface->InteractionText();
}

