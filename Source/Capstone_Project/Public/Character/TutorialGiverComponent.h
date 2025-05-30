// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AkGameplayTypes.h"
#include "TutorialGiverComponent.generated.h"


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

	UPROPERTY(BlueprintReadOnly)
	int Index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class UAkAudioEvent*> TutorialAudio;

	UPROPERTY()
	class UAkComponent* CharacterVoice;

	

	UFUNCTION()
	void OnTutorialAudioComplete();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnAkPostEventCallback PostEventCallback;

	UFUNCTION()
	void StopCallback(
		EAkCallbackType CallbackType,
		UAkCallbackInfo* CallbackInfo);
};
