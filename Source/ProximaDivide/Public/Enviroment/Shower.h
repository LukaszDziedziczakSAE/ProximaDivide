// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Shower.generated.h"

UCLASS()
class PROXIMADIVIDE_API AShower : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleEffect;

	UPROPERTY(VisibleAnywhere)
	bool bIsOn;

	UPROPERTY(EditAnywhere)
	class UAkComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* AmbientSoundOn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* AmbientSoundOff;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;

};
