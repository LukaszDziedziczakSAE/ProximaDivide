// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "SleepArea.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASleepArea : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASleepArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Area;

	UPROPERTY(EditDefaultsOnly)
	float MinExhaustionPercentage = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	int MaxHoursToSleep = 8;

	UFUNCTION()
	int HoursToSleep(APlayerCharacter* PlayerCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;

	UFUNCTION()
	bool CanPlayerSleep(APlayerCharacter* PlayerCharacter);
};
