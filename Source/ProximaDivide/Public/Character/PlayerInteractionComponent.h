// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	class ASurvivalScifi_HUD* HUD;

	UPROPERTY(EditDefaultsOnly)
	float Distance{ 50.0f };

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<class IInteraction> InteractionInterface;

	UFUNCTION()
	void InputModeUI(bool UIMode);

	UPROPERTY(VisibleAnywhere)
	bool IsInUIMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAkAudioEvent* PickUpSound;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	FString GetInteractionText();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	bool InteractableIsCraftingMachine();

	UFUNCTION()
	class ACraftingMachine* GetCraftingMachine();

	UFUNCTION()
	class AContainer* GetContainer();
};
