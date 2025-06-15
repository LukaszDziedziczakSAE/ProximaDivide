// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/PlanetSpinComponent.h"

// Sets default values for this component's properties
UPlanetSpinComponent::UPlanetSpinComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlanetSpinComponent::BeginPlay()
{
	Super::BeginPlay();

	Planet = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
	PlanetSkeleton = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
}


// Called every frame
void UPlanetSpinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Planet != nullptr)
	{
		FRotator Rotation = Planet->GetRelativeRotation();
		Rotation.Yaw += Speed * DeltaTime;
		if (Rotation.Yaw > 360) Rotation.Yaw -= 360;
		Planet->SetRelativeRotation(Rotation);
	}

	else if (PlanetSkeleton != nullptr)
	{
		FRotator Rotation = PlanetSkeleton->GetRelativeRotation();
		Rotation.Yaw += Speed * DeltaTime;
		if (Rotation.Yaw > 360) Rotation.Yaw -= 360;
		PlanetSkeleton->SetRelativeRotation(Rotation);
	}
	
}

