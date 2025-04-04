// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/DroneScanningComponent.h"
#include "Character/Drone.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values for this component's properties
UDroneScanningComponent::UDroneScanningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDroneScanningComponent::BeginPlay()
{
	Super::BeginPlay();

	ScanningEffect = GetOwner<ADrone>()->GetScanningEffect();
	
}


void UDroneScanningComponent::RotateEffect(float DeltaTime)
{
	if (!ScanningEffect->IsActive()) return;

	FRotator Rotation = ScanningEffect->GetRelativeRotation();

	if (bIsAdvancing)
	{
		Rotation.Pitch += RotationSpeed * DeltaTime;
		if (Rotation.Pitch > MaxAngle) bIsAdvancing = !bIsAdvancing;
	}
	else
	{
		Rotation.Pitch -= RotationSpeed * DeltaTime;
		if (Rotation.Pitch < MinAngle) bIsAdvancing = !bIsAdvancing;
	}

	ScanningEffect->SetRelativeRotation(Rotation);
}

// Called every frame
void UDroneScanningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RotateEffect(DeltaTime);
}

