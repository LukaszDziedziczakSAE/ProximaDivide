// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "SurvivalSciFi_Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CAPSTONE_PROJECT_API APlayerCharacter : public ASurvivalSciFi_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UOxygenComponent* OxygenComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerInteractionComponent* PlayerInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* FPS_Arms;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	UCameraComponent* GetCameraComponent() { return CameraComponent; }

};
