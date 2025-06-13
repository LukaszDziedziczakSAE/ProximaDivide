// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/SinkFauset.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ASinkFauset::ASinkFauset()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
	NiagaraEffect->SetupAttachment(Mesh);

	NiagaraEffect->bAutoActivate = false; // Disable auto activation
}

// Called when the game starts or when spawned
void ASinkFauset::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASinkFauset::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

