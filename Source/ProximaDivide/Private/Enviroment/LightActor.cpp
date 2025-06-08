// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/LightActor.h"
#include "Components/PointLightComponent.h"

// Sets default values
ALightActor::ALightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightActor::TurnOnLight()
{
	PointLight->Activate();
}

void ALightActor::TurnOffLight()
{
	PointLight->Deactivate();
}

