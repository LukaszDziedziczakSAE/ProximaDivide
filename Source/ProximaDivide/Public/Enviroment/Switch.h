// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Switch.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASwitch : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<class USwitchActivated> SwitchActivated;

	UPROPERTY(EditAnywhere)
	AActor* Activatee;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	class UAkAudioEvent* SwitchActivatedSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;
};
