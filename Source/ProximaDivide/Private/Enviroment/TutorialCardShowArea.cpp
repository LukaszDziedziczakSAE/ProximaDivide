// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/TutorialCardShowArea.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/PlayerTutorialComponent.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"

// Sets default values
ATutorialCardShowArea::ATutorialCardShowArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SetRootComponent(Area);
	Area->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Area->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ATutorialCardShowArea::BeginPlay()
{
	Super::BeginPlay();
	if (!Area->OnComponentBeginOverlap.IsAlreadyBound(this, &ATutorialCardShowArea::OnBoxBeginOverlap))
	{
		Area->OnComponentBeginOverlap.AddDynamic(this, &ATutorialCardShowArea::OnBoxBeginOverlap);
	}
}


void ATutorialCardShowArea::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnBoxBeginOverlap"));
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr)
	{
		UPlayerTutorialComponent* Tutorial = Player->GetTutorialComponent();
		if (Tutorial != nullptr)
		{
			if (bShowSprintInfo && !Tutorial->GetTutorialState().HasSeenSprintInfo)
			{
				Tutorial->ShowSprintInfo = true;
				Player->GetHUD()->UpdateTutorialInfo();
			}

			else if (bShowLightInfo && !Tutorial->GetTutorialState().HasSeenLightInfo)
			{
				Tutorial->ShowLightInfo = true;
				Player->GetHUD()->UpdateTutorialInfo();
			}

			else if (bShowJumpInfo && !Tutorial->GetTutorialState().SeenJumpInfo)
			{
				Tutorial->ShowJumpInfo = true;
				Player->GetHUD()->UpdateTutorialInfo();
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("Could not find tutorial component on player"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Non player entered tutorial trigger"));
}

// Called every frame
void ATutorialCardShowArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

