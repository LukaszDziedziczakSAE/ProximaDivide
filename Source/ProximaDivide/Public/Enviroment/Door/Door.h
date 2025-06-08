// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SwitchActivated.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum class EDoorMode : uint8
{
	Manual UMETA(DisplayName = "Manual"),
	ManualOpen UMETA(DisplayName = "Manual Open"),
	Automatic UMETA(DisplayName = "Automatic"),
	Offline UMETA(DisplayName = "Offline")
};

UENUM(BlueprintType)
enum class EDoorState : uint8
{
	Closed UMETA(DisplayName = "Closed"),
	Open UMETA(DisplayName = "Open"),
	Opening UMETA(DisplayName = "Opening"),
	Closing UMETA(DisplayName = "Closing")
};

UCLASS()
class PROXIMADIVIDE_API ADoor : public AActor, public ISwitchActivated
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	EDoorMode DoorMode;

	UPROPERTY(EditAnywhere)
	bool Locked;

	UPROPERTY(VisibleAnywhere)
	EDoorState DoorState;

	UPROPERTY(EditAnywhere)
	FVector OpenLocation{ 0, -145.0, 0 };

	UPROPERTY(EditAnywhere)
	FVector ClosedLocation;

	UPROPERTY(EditAnywhere)
	FVector OpenAngle;

	UPROPERTY(EditAnywhere)
	FVector ClosedAngle;

	UPROPERTY(EditAnywhere)
	float Speed{ 250.0f };

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	class UAkComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* DoorOpenEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* DoorCloseEvent;

	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	int CharactersInOverlap;

	UFUNCTION()
	void OpeningTick(float DeltaTime);

	UFUNCTION()
	void ClosingTick(float DeltaTime);

	UFUNCTION()
	bool IsTranslation() { return OpenLocation != ClosedLocation; }

	UFUNCTION()
	bool IsRotation() { return OpenAngle != ClosedAngle; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

	UFUNCTION(BlueprintCallable)
	void ToggleState();

	virtual void SwitchActivation() override;

	virtual FString InteractionText() override;

	UFUNCTION(BlueprintCallable)
	void Lock() { Locked = true; }

	UFUNCTION(BlueprintCallable)
	void Unlock() { Locked = false; }

	UFUNCTION()
	void SetMode(EDoorMode Mode) { DoorMode = Mode; }

	UFUNCTION(BlueprintPure)
	EDoorState GetDoorState() { return DoorState; }

	UFUNCTION()
	void SetDoorMode(EDoorMode NewDoorMode);
};
