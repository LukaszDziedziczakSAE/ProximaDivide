// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/ObjectiveGoToArea.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"

// Sets default values
AObjectiveGoToArea::AObjectiveGoToArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SetRootComponent(Area);
	Area->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Area->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void AObjectiveGoToArea::BeginPlay()
{
	Super::BeginPlay();
	Area->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveGoToArea::OnBoxBeginOverlap);
}

void AObjectiveGoToArea::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr)
	{

	}
}

// Called every frame
void AObjectiveGoToArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

