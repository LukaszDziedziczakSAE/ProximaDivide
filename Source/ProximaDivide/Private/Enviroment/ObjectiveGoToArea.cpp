// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/ObjectiveGoToArea.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Notifications/ObjectiveMarker_UserWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerObjectivesComponent.h"

// Sets default values
AObjectiveGoToArea::AObjectiveGoToArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SetRootComponent(Area);
	Area->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Area->SetEnableGravity(false);

	ObjectiveMarkerComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ObjectiveMarkerComponent"));
	ObjectiveMarkerComponent->SetupAttachment(RootComponent);
	ObjectiveMarkerComponent->SetWidgetSpace(EWidgetSpace::Screen);
	ObjectiveMarkerComponent->SetVisibility(false); // Start hidden
}

// Called when the game starts or when spawned
void AObjectiveGoToArea::BeginPlay()
{
	Super::BeginPlay();
	if (!Area->OnComponentBeginOverlap.IsAlreadyBound(this, &AObjectiveGoToArea::OnBoxBeginOverlap))
	{
		Area->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveGoToArea::OnBoxBeginOverlap);
	}

	if (Tags.Num() == 0)
		UE_LOG(LogTemp, Warning, TEXT("%s has no tag"), *GetName());
}

void AObjectiveGoToArea::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBoxBeginOverlap"));
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr && Tags.Num() > 0)
	{
		Player->GetObjectivesComponent()->OnArriveAtObjective(Tags[0]);
	}
}

// Called every frame
void AObjectiveGoToArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjectiveGoToArea::ShowObjectiveMarker()
{
	if (ObjectiveMarkerComponent)
	{
		if (ObjectiveMarkerComponent->GetWidgetClass() != ObjectiveMarkerWidgetClass)
		{
			ObjectiveMarkerComponent->SetWidgetClass(ObjectiveMarkerWidgetClass);
			ObjectiveMarkerComponent->InitWidget();
		}

		if (UObjectiveMarker_UserWidget* Widget = Cast<UObjectiveMarker_UserWidget>(ObjectiveMarkerComponent->GetUserWidgetObject()))
		{
			Widget->SetMarkerText(MarkerText);
			Widget->Owner = ObjectiveMarkerComponent;
			Widget->Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
		}
		ObjectiveMarkerComponent->SetVisibility(true);
	}
}

void AObjectiveGoToArea::HideObjectiveMarker()
{
	if (ObjectiveMarkerComponent)
	{
		ObjectiveMarkerComponent->SetVisibility(false);
		ObjectiveMarkerComponent->DestroyComponent();
		ObjectiveMarkerComponent = nullptr;
	}
}

