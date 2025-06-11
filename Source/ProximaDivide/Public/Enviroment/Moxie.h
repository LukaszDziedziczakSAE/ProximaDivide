// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Interface/ObjectiveMarkerInterface.h"
#include "Moxie.generated.h"

UCLASS()
class PROXIMADIVIDE_API AMoxie : public AActor, public IInteraction, public IObjectiveMarkerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoxie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UAkComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* AmbientSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAkAudioEvent* MoxieUseSound;

	UPROPERTY(EditAnywhere)
	float Stored;

	UPROPERTY(EditDefaultsOnly)
	float Capacity = 120.0f;

	UPROPERTY(EditDefaultsOnly)
	float RechargeRate = 0.25f;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 5.0f;

	UPROPERTY(VisibleAnywhere)
	float CooldownTimer;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* ObjectiveMarkerComponent;

	UPROPERTY(EditAnywhere, Category = "Objective Marker")
	TSubclassOf<class UObjectiveMarker_UserWidget> ObjectiveMarkerWidgetClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Marker")
	FText MarkerText;

	// Inherited via IObjectiveMarkerInterface
	virtual void ShowObjectiveMarker() override;
	virtual void HideObjectiveMarker() override;
};
