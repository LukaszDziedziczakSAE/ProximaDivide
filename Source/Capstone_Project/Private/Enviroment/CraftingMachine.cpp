// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/CraftingMachine.h"
#include "Components/BoxComponent.h"
#include "UI/SurvivalScifi_HUD.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


// Sets default values
ACraftingMachine::ACraftingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Machine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crafting Machine Mesh"));
	SetRootComponent(Machine);

	InteractionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collider"));
	InteractionCollider->SetupAttachment(Machine);

	Tray = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tray Mesh"));
	Tray->SetupAttachment(Machine);

	CraftingItemPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Crafting Item Position"));
	CraftingItemPosition->SetupAttachment(Machine);

	CraftingLaser = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Crafting Laser"));
	CraftingLaser->SetupAttachment(Machine);
}

// Called when the game starts or when spawned
void ACraftingMachine::BeginPlay()
{
	Super::BeginPlay();
	
	ClosedAngle = Tray->GetRelativeRotation().Pitch;
}

// Called every frame
void ACraftingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CraftingMachineState)
	{
	case ECraftingMachineState::Opening:
		OpeningTick(DeltaTime);
		break;

	case ECraftingMachineState::Closing:
		ClosingTick(DeltaTime);
		break;

	case ECraftingMachineState::Crafting:
		CraftingTick(DeltaTime);
		break;
	}
}

void ACraftingMachine::OpeningTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = FMath::Lerp(ClosedAngle, OpenAngle, GetProgress());
		Tray->SetRelativeRotation(Rotation);
	}
	else
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = OpenAngle;
		Tray->SetRelativeRotation(Rotation);
		CraftingMachineState = ECraftingMachineState::Standby;

		CraftingLaser->Activate();
		CraftingLaser->SetVectorParameter(TEXT("BeamEndVec"), CraftingItemPosition->GetComponentLocation());
	}
}

void ACraftingMachine::ClosingTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = FMath::Lerp(OpenAngle, ClosedAngle, GetProgress());
		Rotation.Yaw = -90.0f;
		Rotation.Roll = -90.0f;
		Tray->SetRelativeRotation(Rotation);
	}
	else
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = ClosedAngle;
		Tray->SetRelativeRotation(Rotation);
		CraftingMachineState = ECraftingMachineState::Closed;
	}
}

void ACraftingMachine::CraftingTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{

	}
	else
	{
		CraftingMachineState = ECraftingMachineState::Standby;
	}
}

void ACraftingMachine::Interact(APlayerCharacter* PlayerCharacter)
{
	// start crafting process
	if (CraftingMachineState == ECraftingMachineState::Closed)
	{
		Timer = OpenCloseTime;
		CraftingMachineState = ECraftingMachineState::Opening;

		GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->ShowCraftingMenu();
	}

	else if (CraftingMachineState == ECraftingMachineState::Standby)
	{
		Timer = OpenCloseTime;
		CraftingMachineState = ECraftingMachineState::Closing;

		GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->HideCraftingMenu();

		CraftingLaser->Deactivate();
	}
}

FString ACraftingMachine::InteractionText()
{
	switch (CraftingMachineState)
	{
	case ECraftingMachineState::Closed: return TEXT("Craft");

	default: return TEXT("");
	}
	
}

float ACraftingMachine::GetProgress()
{
	switch (CraftingMachineState)
	{
	case ECraftingMachineState::Opening:
		return 1 - (Timer / OpenCloseTime);

	case ECraftingMachineState::Closing:
		return 1 - (Timer / OpenCloseTime);

	default: return 1.0f;
	}
}

