// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Door.h"
#include "Components/BoxComponent.h"
#include "Character/SurvivalSciFi_Character.h"
#include "AkGameplayStatics.h"
#include "AkComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(Root);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);

	AudioComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnColliderBeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnColliderEndOverlap);

	ClosedLocation = DoorMesh->GetRelativeLocation();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (DoorState)
	{
	case EDoorState::Opening:
		OpeningTick(DeltaTime);
		break;
	case EDoorState::Closing:
		ClosingTick(DeltaTime);
		break;
	}
}

void ADoor::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	class ASurvivalSciFi_Character* Character = Cast<ASurvivalSciFi_Character>(OtherActor);
	if (Character != nullptr) CharactersInOverlap++;

	if (!Locked && DoorMode == EDoorMode::Automatic && CharactersInOverlap > 0)
		Open();
}

void ADoor::OnColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	class ASurvivalSciFi_Character* Character = Cast<ASurvivalSciFi_Character>(OtherActor);
	if (Character != nullptr) CharactersInOverlap--;

	if (!Locked && (DoorMode == EDoorMode::Automatic || DoorMode == EDoorMode::ManualOpen) && CharactersInOverlap == 0)
		Close();
}

void ADoor::OpeningTick(float DeltaTime)
{
	FVector Step = (OpenLocation - ClosedLocation);
	Step.Normalize();
	Step *= DeltaTime * Speed;

	if (FVector::Distance(DoorMesh->GetRelativeLocation(), OpenLocation) > Step.Length())
	{
		DoorMesh->SetRelativeLocation(DoorMesh->GetRelativeLocation() + Step);
	}
	else
	{
		DoorMesh->SetRelativeLocation(OpenLocation);
		DoorState = EDoorState::Open;
	}
}

void ADoor::ClosingTick(float DeltaTime)
{
	FVector Step = (ClosedLocation - OpenLocation);
	Step.Normalize();
	Step *= DeltaTime * Speed;

	if (FVector::Distance(DoorMesh->GetRelativeLocation(), ClosedLocation) > Step.Length())
	{
		DoorMesh->SetRelativeLocation(DoorMesh->GetRelativeLocation() + Step);
	}
	else
	{
		DoorMesh->SetRelativeLocation(ClosedLocation);
		DoorState = EDoorState::Closed;
	}
}

void ADoor::Open()
{
	if (DoorState == EDoorState::Closed)
	{
		DoorState = EDoorState::Opening;
		//UAkGameplayStatics::PostEvent(DoorOpenEvent, this, int32(0), FOnAkPostEventCallback(), true);
		AudioComponent->PostAkEvent(DoorOpenEvent, int32(0), FOnAkPostEventCallback());
	}
}

void ADoor::Close()
{
	if (DoorState == EDoorState::Open)
	{
		DoorState = EDoorState::Closing;
		//UAkGameplayStatics::PostEvent(DoorCloseEvent, this, int32(0), FOnAkPostEventCallback(), true);
		AudioComponent->PostAkEvent(DoorCloseEvent, int32(0), FOnAkPostEventCallback());
	}
}

void ADoor::ToggleState()
{
	UE_LOG(LogTemp, Warning, TEXT("Door state toggled"));

	if (DoorState == EDoorState::Open) 
		DoorState = EDoorState::Closing;
	
	else if (DoorState == EDoorState::Closed) 
		DoorState = EDoorState::Opening;
}

void ADoor::SwitchActivation()
{
	switch (DoorMode)
	{
	case EDoorMode::Manual:
		ToggleState();
		break;
		
	case EDoorMode::ManualOpen:
		if (CharactersInOverlap > 0) ToggleState();
		break;
	}

	
}

FString ADoor::InteractionText()
{
	if (DoorState == EDoorState::Closed)
		return TEXT("Open Door");

	else if (DoorState == EDoorState::Open)
		return TEXT("Close Door");

	return TEXT("");
}

void ADoor::SetDoorMode(EDoorMode NewDoorMode)
{
	DoorMode = NewDoorMode;
}

