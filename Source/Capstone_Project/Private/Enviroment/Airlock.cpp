// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Airlock.h"
#include "Enviroment/Door.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "AkGameplayStatics.h"
#include "AkComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/PlayerCharacter.h"
#include "Game/SurvivalScifiGameMode.h"

// Sets default values
AAirlock::AAirlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Light = CreateDefaultSubobject<UPointLightComponent >(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);

	AudioComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Root);

	VentingVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Venting VFX"));
	VentingVFX->SetupAttachment(Root);
}

bool AAirlock::DoorsClosed()
{
	return InnerDoor->GetDoorState() == EDoorState::Closed 
		&& OuterDoor->GetDoorState() == EDoorState::Closed;
}

void AAirlock::SetDoorModes()
{
	switch (AirlockState)
	{
	case EAirlockState::OpenIn:
		InnerDoor->SetDoorMode(EDoorMode::Automatic);
		OuterDoor->SetDoorMode(EDoorMode::ManualOpen);
		break;

	case EAirlockState::OpenOut:
		InnerDoor->SetDoorMode(EDoorMode::ManualOpen);
		OuterDoor->SetDoorMode(EDoorMode::Automatic);
		break;
	}
}

void AAirlock::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	BeginCycling();
	PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
}

void AAirlock::OnColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AAirlock::BeginCycling()
{
	if (AirlockState == EAirlockState::OpenIn) AirlockState = EAirlockState::CyclingOut;
	else if (AirlockState == EAirlockState::OpenOut) AirlockState = EAirlockState::CyclingIn;
	else return;

	OuterDoor->Close();
	InnerDoor->Close();
	Timer = CycleTime;
	Light->SetLightColor(CyclingColor);
	bHasPlayedCycleSound = false;
	VentingVFX->Activate();
}

// Called when the game starts or when spawned
void AAirlock::BeginPlay()
{
	Super::BeginPlay();
	
	StandbyColor = Light->GetLightColor();

	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors);
	for (AActor* ChildActor : ChildActors)
	{
		if (ChildActor->ActorHasTag(TEXT("Inner")))
			InnerDoor = Cast<ADoor>(ChildActor);

		else if (ChildActor->ActorHasTag(TEXT("Outer")))
			OuterDoor = Cast<ADoor>(ChildActor);
	}

	SetDoorModes();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAirlock::OnColliderBeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AAirlock::OnColliderEndOverlap);
}

void AAirlock::OverridePlayerStartTag()
{
	if (PlayerStartTagOverride == "") return;


}

// Called every frame
void AAirlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((AirlockState == EAirlockState::CyclingIn || AirlockState == EAirlockState::CyclingOut)
		&& DoorsClosed())
	{
		if (!bHasPlayedCycleSound)
		{
			AudioComponent->PostAkEvent(AirlockCycleSound, int32(0), FOnAkPostEventCallback());
			bHasPlayedCycleSound = true;
		}
		

		Timer -= DeltaTime;

		if (Timer <= 0) // cycle complete
		{
			if (AirlockState == EAirlockState::CyclingIn)
			{
				AirlockState = EAirlockState::OpenIn;
				InnerDoor->Open();
			}

			else if (AirlockState == EAirlockState::CyclingOut)
			{
				AirlockState = EAirlockState::OpenOut;
				OuterDoor->Open();
			}

			SetDoorModes();
			Light->SetLightColor(StandbyColor);
			VentingVFX->Deactivate();

			if (PlayerCharacter != nullptr)
			{
				PlayerCharacter->bIsInside = AirlockState == EAirlockState::OpenIn;
				if (PlayerCharacter->bIsInside && PlayerStartTagOverride != "" && PlayerStartTagOverride != "None" && PlayerStartTagOverride != "none")
				{
					Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode())->UpdatePlayerStartTag(PlayerStartTagOverride);
				}
			}
		}
	}
}

void AAirlock::OuterSwitchPress()
{
	//UE_LOG(LogTemp, Warning, TEXT("Outer Switch Press"));

	if (AirlockState == EAirlockState::OpenOut)
	{
		OuterDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenIn)
	{
		BeginCycling();
	}
}

void AAirlock::InnerSwitchPress()
{
	//UE_LOG(LogTemp, Warning, TEXT("Inner Switch Press"));

	if (AirlockState == EAirlockState::OpenIn)
	{
		InnerDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenOut)
	{
		BeginCycling();
	}
}

void AAirlock::InsideInnerSwitchPress()
{
	//UE_LOG(LogTemp, Warning, TEXT("Inside Inner Switch Press"));

	if (AirlockState == EAirlockState::OpenIn)
	{
		InnerDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenOut)
	{
		BeginCycling();
	}
}

void AAirlock::InsideOuterSwitchPress()
{
	//UE_LOG(LogTemp, Warning, TEXT("Inside Outer Switch Press"));

	if (AirlockState == EAirlockState::OpenOut)
	{
		OuterDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenIn)
	{
		BeginCycling();
	}
}
