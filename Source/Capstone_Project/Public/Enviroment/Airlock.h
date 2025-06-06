// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SwitchActivated.h"
#include "Airlock.generated.h"

UENUM(BlueprintType)
enum class EAirlockState : uint8
{
	OpenOut UMETA(DisplayName = "Open Out"),
	OpenIn UMETA(DisplayName = "Open In"),
	CyclingIn UMETA(DisplayName = "Cycling In"),
	CyclingOut UMETA(DisplayName = "Cycling Out")
};

UCLASS()
class CAPSTONE_PROJECT_API AAirlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAirlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class ADoor* InnerDoor;

	UPROPERTY(EditAnywhere)
	ADoor* OuterDoor;

	UPROPERTY(EditDefaultsOnly)
	float CycleTime{ 2.0f };

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	class UPointLightComponent* Light;

	UPROPERTY(EditAnywhere)
	EAirlockState AirlockState;

	UPROPERTY(EditAnywhere)
	FLinearColor CyclingColor;

	UPROPERTY(VisibleAnywhere)
	FLinearColor StandbyColor;

	UPROPERTY(EditAnywhere)
	class UAkComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* AirlockCycleSound;

	UPROPERTY(VisibleAnywhere)
	bool bHasPlayedCycleSound;

	UPROPERTY()
	float Timer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystemComponent* VentingVFX;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* PlayerCharacter;

	UFUNCTION()
	bool DoorsClosed();

	UFUNCTION()
	void SetDoorModes();

	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void BeginCycling();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlayerStartTagOverride;

	UFUNCTION()
	void OverridePlayerStartTag();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OuterSwitchPress();

	UFUNCTION()
	void InnerSwitchPress();

	UFUNCTION()
	void InsideInnerSwitchPress();

	UFUNCTION()
	void InsideOuterSwitchPress();

	UFUNCTION()
	EAirlockState GetAirlockState() { return AirlockState; }
};
