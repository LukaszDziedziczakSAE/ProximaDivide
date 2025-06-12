// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AkGameplayTypes.h"
#include "PlayerSuitVoiceComponent.generated.h"

USTRUCT()
struct FBeginPlayEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UAkAudioEvent* AkAudioEvent = nullptr;

	UPROPERTY(EditAnywhere)
	FName MapName;

	UPROPERTY(EditAnywhere)
	FName PlayerStartTag;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UPlayerSuitVoiceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerSuitVoiceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<FBeginPlayEvent> BeginPlayEvents;

	UPROPERTY(VisibleAnywhere)
	TArray<UAkAudioEvent*> PlayQueue;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* Player;

	UPROPERTY(VisibleAnywhere)
	bool bIsPlaying;

	UPROPERTY(VisibleAnywhere)
	bool bPreventQueue;

	UPROPERTY()
	FOnAkPostEventCallback PostEventCallback;

	UFUNCTION()
	void PlaybackComplete();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Play(UAkAudioEvent* AkAudioEvent, bool PreventQueue = false);

	UFUNCTION(BlueprintPure)
	bool IsPlaying() const { return bIsPlaying; }
};
