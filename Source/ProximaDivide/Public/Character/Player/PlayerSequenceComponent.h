// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSequenceComponent.generated.h"

USTRUCT()
struct FBeginPlaySequence
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    class ULevelSequence* LevelSequence = nullptr;

	UPROPERTY(EditAnywhere)
	FName MapName;

	UPROPERTY(EditAnywhere)
	FName PlayerStartTag;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMADIVIDE_API UPlayerSequenceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerSequenceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnLevelSeqenceComplete();

	UPROPERTY(EditAnywhere)
	TArray<FBeginPlaySequence> BeginPlaySequences;

	UPROPERTY(VisibleAnywhere)
	bool bIsPlayingSequence;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* Player;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PlayLevelSequence(class ULevelSequence* LevelSequence);

	UFUNCTION(BlueprintPure)
	bool IsPlayingSequence() { return bIsPlayingSequence; }
};
