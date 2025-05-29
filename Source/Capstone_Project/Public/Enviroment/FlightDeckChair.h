// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "FlightDeckChair.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API AFlightDeckChair : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlightDeckChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Chair;

	UPROPERTY(EditAnywhere)
	class UAkAudioEvent* MusicChange;

	UPROPERTY(EditAnywhere)
	USceneComponent* PlayerPosition;

	UPROPERTY(EditAnywhere)
	class ULevelSequence* LevelSequence;

	UFUNCTION()
	void OnLevelSeqenceComplete();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText() override;

};
