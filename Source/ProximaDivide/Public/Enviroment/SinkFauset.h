// Written and owned by Lukasz Dziedziczak. Copywrite 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SinkFauset.generated.h"

UCLASS()
class PROXIMADIVIDE_API ASinkFauset : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASinkFauset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
