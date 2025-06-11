// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ObjectiveMarkerInterface.h"
#include "ObjectiveGoToArea.generated.h"

UCLASS()
class PROXIMADIVIDE_API AObjectiveGoToArea : public AActor, public IObjectiveMarkerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveGoToArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Area;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* ObjectiveMarkerComponent;

	UPROPERTY(EditAnywhere, Category = "Objective Marker")
	TSubclassOf<class UObjectiveMarker_UserWidget> ObjectiveMarkerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Marker")
	FText MarkerText;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// IObjectiveMarkerInterface
	virtual void ShowObjectiveMarker() override;
	virtual void HideObjectiveMarker() override;
};
