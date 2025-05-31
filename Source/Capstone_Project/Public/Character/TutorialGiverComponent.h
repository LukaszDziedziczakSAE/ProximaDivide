// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AkGameplayTypes.h"
#include "TutorialGiverComponent.generated.h"

UENUM(BlueprintType)
enum ETutorialCondition
{
	OnAudioFinish,
	OnLookAround,
	OnMoveAround,
	PickupItem,
	ConsumeItem,
	OpenInventory,
	ClosedInventory
};

USTRUCT(BlueprintType)
struct FTutorialPart
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAkAudioEvent* TutorialAudio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETutorialCondition> TutorialCondition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "On Start")
	bool ShowMouseMoveInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "On Start")
	bool ShowMovementInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "On Start")
	bool ShowInventoryInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "On Start")
	bool ShowSlotInfo;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_PROJECT_API UTutorialGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialGiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Index = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int AudioIndex = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ObjectivePrecomplete;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTutorialPart> TutorialParts;

	UPROPERTY()
	class UAkComponent* CharacterVoice;

	UPROPERTY()
	class APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AWaypoint* StartWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AWaypoint* EndWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* FlightDeckChair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USurvivalScifi_AnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* SitDownMontage;

	UFUNCTION()
	void OnPartStart();

	UFUNCTION()
	void OnSitComplete();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnAkPostEventCallback PostEventCallback;

	UFUNCTION()
	void PlaybackComplete(EAkCallbackType CallbackType,	UAkCallbackInfo* CallbackInfo);

	UFUNCTION()
	void GoToNextPart();

	UFUNCTION()
	FTutorialPart GetCurrentPart();

	UFUNCTION()
	void BeginTutorial();

	UFUNCTION()
	void CompleteTutorial();

	UFUNCTION(BlueprintPure)
	bool IsInProgress() { return Index >= 0 && Index < TutorialParts.Num(); }

	UFUNCTION(BlueprintPure)
	AWaypoint* GetStartWaypoint() { return StartWaypoint; }

	UFUNCTION(BlueprintPure)
	AWaypoint* GetEndWaypoint() { return EndWaypoint; }

	UFUNCTION(BlueprintPure)
	AActor* GetFlightDeckChair() { return FlightDeckChair; }
	
	UPROPERTY(VisibleAnywhere)
	bool HasCompleted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AAstronaut_AIController* AI;

	UFUNCTION()
	void PlaySitDownAnimation();

	UFUNCTION()
	bool ReadyToSitDown() { return SitDownMontage != nullptr; }
};
