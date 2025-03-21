// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/OxygenComponent.h"
#include "Character/PlayerInteractionComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	//CameraComponent->SetupAttachment(GetMesh(), TEXT("Head"));
	CameraComponent->bUsePawnControlRotation = true;

	OxygenComponent = CreateDefaultSubobject< UOxygenComponent>(TEXT("Oxygen"));

	PlayerInteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("Player Interaction Component"));

	FPS_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	FPS_Arms->SetupAttachment(CameraComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

