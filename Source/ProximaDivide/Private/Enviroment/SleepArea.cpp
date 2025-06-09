// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/SleepArea.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Components/ExhaustionComponent.h"
#include "Game/SurvivalSciFi_GameInstance.h"

// Sets default values
ASleepArea::ASleepArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SetRootComponent(Area);
	Area->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Area->SetEnableGravity(false);
	Area->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ASleepArea::BeginPlay()
{
	Super::BeginPlay();
	
}

int ASleepArea::HoursToSleep(APlayerCharacter* PlayerCharacter)
{
	return FMath::CeilToInt(PlayerCharacter->GetExhaustionComponent()->GetMissingPercentage() * MaxHoursToSleep);
}

// Called every frame
void ASleepArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASleepArea::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!CanPlayerSleep(PlayerCharacter)) return;

	PlayerCharacter->GetExhaustionComponent()->SetValue(0);
	GetGameInstance<USurvivalSciFi_GameInstance>()->StartWakeFromSleep(HoursToSleep(PlayerCharacter));
}

FString ASleepArea::InteractionText(APlayerCharacter* PlayerCharacter)
{
	if (!CanPlayerSleep(PlayerCharacter)) return TEXT("");
	return TEXT("go to Sleep");
}

bool ASleepArea::CanPlayerSleep(APlayerCharacter* PlayerCharacter)
{
	return PlayerCharacter->GetExhaustionComponent()->GetPercentage() >= MinExhaustionPercentage;
}

