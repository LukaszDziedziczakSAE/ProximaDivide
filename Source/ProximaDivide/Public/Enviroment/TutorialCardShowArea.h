// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialCardShowArea.generated.h"

UCLASS()
class PROXIMADIVIDE_API ATutorialCardShowArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialCardShowArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Area;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	bool bShowSprintInfo;

	UPROPERTY(EditAnywhere)
	bool bShowLightInfo;

	UPROPERTY(EditAnywhere)
	bool bShowJumpInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
