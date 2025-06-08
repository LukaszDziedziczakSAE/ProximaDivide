// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbienceAndMusic.generated.h"

UCLASS()
class PROXIMADIVIDE_API AAmbienceAndMusic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmbienceAndMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UAkStateValue* AmbienceState;

	UPROPERTY(EditAnywhere)
	class UAkAudioEvent* Ambience;

	UPROPERTY(EditAnywhere)
	UAkAudioEvent* Music;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
