// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/SurvivalSciFi_Character.h"
#include "Item/InventoryComponent.h"
#include "Character/HealthComponent.h"
#include "Character/PaperdollComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASurvivalSciFi_Character::ASurvivalSciFi_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	PaperdollComponent = CreateDefaultSubobject<UPaperdollComponent>(TEXT("Paperdoll"));
}

// Called when the game starts or when spawned
void ASurvivalSciFi_Character::BeginPlay()
{
	Super::BeginPlay();
	SetMovementSpeed(false);
}

// Called every frame
void ASurvivalSciFi_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASurvivalSciFi_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASurvivalSciFi_Character::SetMovementSpeed(bool IsRunning)
{
	GetCharacterMovement()->MaxWalkSpeed = IsRunning ? RunningSpeed : WalkingSpeed;
}

