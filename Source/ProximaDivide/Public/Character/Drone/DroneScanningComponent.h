// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneScanningComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UDroneScanningComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDroneScanningComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float MinAngle;

	UPROPERTY(EditDefaultsOnly)
	float MaxAngle;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed;

	UFUNCTION()
	void RotateEffect(float DeltaTime);

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* ScanningEffect;

	UPROPERTY(VisibleAnywhere)
	bool bIsAdvancing;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
