// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbientSoundActor.generated.h"

UCLASS()
class PROXIMADIVIDE_API AAmbientSoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmbientSoundActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UAkComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAkAudioEvent* AmbientSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
