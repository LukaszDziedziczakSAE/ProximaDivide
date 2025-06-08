// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Enviroment/EEnviroment.h"
#include "FlightDeckChair.generated.h"

UCLASS()
class PROXIMADIVIDE_API AFlightDeckChair : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlightDeckChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class USurvivalSciFi_GameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Chair;

	UPROPERTY(EditAnywhere)
	class UAkAudioEvent* MusicChange;

	UPROPERTY(EditAnywhere)
	USceneComponent* PlayerPosition;

	UPROPERTY(EditAnywhere, Category = "Level Sequence")
	class ULevelSequence* LevelSequence;

	UPROPERTY(EditAnywhere, Category = "Level Sequence")
	EEnviroment SequenceEnviroment;

	UFUNCTION()
	void OnLevelSeqenceComplete();

	UPROPERTY(EditAnywhere, Category = "Post Sequence")
	FName NewMapName = TEXT("L_Mars");

	UPROPERTY(EditAnywhere, Category = "Post Sequence")
	FName PlayerStartTag = TEXT("crash");

	UPROPERTY(EditAnywhere, Category = "Post Sequence")
	EEnviroment PostSequenceEnviroment;

	UPROPERTY(EditAnywhere, Category = "Level Sequence")
	FName TitleCardEventName;

	UPROPERTY(VisibleAnywhere)
	APlayerCharacter* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText() override;

	UFUNCTION()
	void ReceiveNotify(FName EventName);

};
