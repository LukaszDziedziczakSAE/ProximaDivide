// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/Components/StatComponent.h"
#include "Character/Player/PlayerCharacter.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = GetOwner<APlayerCharacter>();
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentValue = FMath::Clamp(CurrentValue + (ModifyPerSecond * DeltaTime), 0, MaxValue);
}

void UStatComponent::ModifyValue(float ModifyAmount)
{
	CurrentValue = FMath::Clamp(CurrentValue + ModifyAmount, 0, MaxValue);
}

