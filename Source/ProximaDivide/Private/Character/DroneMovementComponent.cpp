// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/DroneMovementComponent.h"
#include "Character/Drone.h"

// Sets default values for this component's properties
UDroneMovementComponent::UDroneMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDroneMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Drone = GetOwner<ADrone>();
	
}


void UDroneMovementComponent::Hovering(float DeltaTime)
{
	FVector RelativeLocation = Drone->GetMesh()->GetRelativeLocation();

	if (bIsHoveringUp)
	{
		RelativeLocation.Z += HoverSpeed * DeltaTime;
		if (RelativeLocation.Z > MaxHeight) bIsHoveringUp = !bIsHoveringUp;
	}
	else
	{
		RelativeLocation.Z -= HoverSpeed * DeltaTime;
		if (RelativeLocation.Z < MinHeigh) bIsHoveringUp = !bIsHoveringUp;
	}

	Drone->GetMesh()->SetRelativeLocation(RelativeLocation);
}

// Called every frame
void UDroneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Hovering(DeltaTime);
}

