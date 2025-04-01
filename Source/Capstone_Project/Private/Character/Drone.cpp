// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Drone.h"
#include "Character/DroneScanningComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	DroneScanningComponent = CreateDefaultSubobject<UDroneScanningComponent>(TEXT("Drone Scanning Component"));

	ScanningEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Scanning Effect"));
	ScanningEffect->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

