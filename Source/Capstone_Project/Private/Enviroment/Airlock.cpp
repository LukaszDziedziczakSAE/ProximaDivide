// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/Airlock.h"
#include "Enviroment/Door.h"
#include "Components/PointLightComponent.h"

// Sets default values
AAirlock::AAirlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Light = CreateDefaultSubobject<UPointLightComponent >(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
}

bool AAirlock::DoorsClosed()
{
	return InnerDoor->GetDoorState() == EDoorState::Closed 
		&& OuterDoor->GetDoorState() == EDoorState::Closed;
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
}

// Called every frame
void AAirlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((AirlockState == EAirlockState::CyclingIn || AirlockState == EAirlockState::CyclingOut)
		&& DoorsClosed())
	{
		Timer -= DeltaTime;

		if (Timer <= 0)
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

			Light->SetLightColor(StandbyColor);
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
		OuterDoor->Close();
		InnerDoor->Close();
		Timer = CycleTime;
		AirlockState = EAirlockState::CyclingOut;
		Light->SetLightColor(CyclingColor);
	}
}

void AAirlock::InnerSwitchPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Inner Switch Press"));

	if (AirlockState == EAirlockState::OpenIn)
	{
		InnerDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenOut)
	{
		OuterDoor->Close();
		InnerDoor->Close();
		Timer = CycleTime;
		AirlockState = EAirlockState::CyclingIn;
		Light->SetLightColor(CyclingColor);
	}
}

void AAirlock::InsideInnerSwitchPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Inside Inner Switch Press"));

	if (AirlockState == EAirlockState::OpenIn)
	{
		InnerDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenOut)
	{
		OuterDoor->Close();
		InnerDoor->Close();
		Timer = CycleTime;
		AirlockState = EAirlockState::CyclingIn;
		Light->SetLightColor(CyclingColor);
	}
}

void AAirlock::InsideOuterSwitchPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Inside Outer Switch Press"));

	if (AirlockState == EAirlockState::OpenOut)
	{
		OuterDoor->Open();
	}

	else if (AirlockState == EAirlockState::OpenIn)
	{
		OuterDoor->Close();
		InnerDoor->Close();
		Timer = CycleTime;
		AirlockState = EAirlockState::CyclingOut;
		Light->SetLightColor(CyclingColor);
	}
}
