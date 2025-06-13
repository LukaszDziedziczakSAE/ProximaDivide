// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Interface/ObjectiveMarkerInterface.h"
#include "SleepArea.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASleepArea : public AActor, public IInteraction, public IObjectiveMarkerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASleepArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Area;

	UPROPERTY(EditDefaultsOnly)
	float MinExhaustionPercentage = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	int MaxHoursToSleep = 8;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* ObjectiveMarkerComponent;

	UPROPERTY(EditAnywhere, Category = "Objective Marker")
	TSubclassOf<class UObjectiveMarker_UserWidget> ObjectiveMarkerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Marker")
	FText MarkerText;

	UFUNCTION()
	int HoursToSleep(APlayerCharacter* PlayerCharacter);

	UPROPERTY(EditAnywhere, Category = "Level Sequence")
	class ULevelSequence* LevelSequence;

	UFUNCTION()
	void OnLevelSeqenceComplete();

	UPROPERTY(VisibleAnywhere)
	int CurrentHoursToSleep = -1;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* Player;

	UPROPERTY(EditAnywhere)
	class APlayerStart* PlayerStart;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual FString InteractionText(APlayerCharacter* PlayerCharacter) override;

	UFUNCTION()
	bool CanPlayerSleep(APlayerCharacter* PlayerCharacter);

	// IObjectiveMarkerInterface
	virtual void ShowObjectiveMarker() override;
	virtual void HideObjectiveMarker() override;

	UFUNCTION(BlueprintCallable)
	FName GetPlayerStartTag();
};
