// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UDroneMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDroneMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float MinHeigh;

	UPROPERTY(EditDefaultsOnly)
	float MaxHeight;

	UPROPERTY(EditDefaultsOnly)
	float HoverSpeed;

	UFUNCTION()
	void Hovering(float DeltaTime);

	UPROPERTY(VisibleAnywhere)
	class ADrone* Drone;

	UPROPERTY(VisibleAnywhere)
	bool bIsHoveringUp;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
