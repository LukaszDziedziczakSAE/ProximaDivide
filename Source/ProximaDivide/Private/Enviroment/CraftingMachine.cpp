// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Enviroment/CraftingMachine.h"
#include "Components/BoxComponent.h"
#include "UI/SurvivalScifi_HUD.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Item/ItemDataAsset.h"
#include "Item/SurvivalScifi_Item.h"
#include "AkGameplayStatics.h"
#include "Item/InventoryComponent.h"
#include "Character/PlayerCharacter.h"


ACraftingMachine::ACraftingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Machine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crafting Machine Mesh"));
	SetRootComponent(Machine);

	InteractionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collider"));
	InteractionCollider->SetupAttachment(Machine);

	Tray = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tray Mesh"));
	Tray->SetupAttachment(Machine);

	CraftingItemPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Crafting Item Position"));
	CraftingItemPosition->SetupAttachment(Machine);

	CraftingLaser = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Crafting Laser"));
	CraftingLaser->SetupAttachment(Machine);
}

void ACraftingMachine::BeginPlay()
{
	Super::BeginPlay();
	
	ClosedAngle = Tray->GetRelativeRotation().Pitch;
}

float ACraftingMachine::GetLaserHeight()
{
	float StartingHeight = CraftingItemPosition->GetComponentLocation().Z;
	float EndHeight = StartingHeight + CurrentlyCraftingItem->GetBoxExtent().Z + CurrentlyCrafting->CraftingLaserHeightOffset;

	return FMath::Lerp(StartingHeight, EndHeight, GetProgress());
}

FVector ACraftingMachine::GetLaserPosition(float DeltaTime)
{
	CurrentLaserPoint.Z = GetLaserHeight();
	TargetLaserPoint.Z = CurrentLaserPoint.Z;

	FVector Step = TargetLaserPoint - CurrentLaserPoint;
	Step.Normalize();
	Step *= LaserMovementSpeed * DeltaTime;

	if (Step.Length() > FVector::Distance(CurrentLaserPoint, TargetLaserPoint))
	{
		CurrentLaserPoint += Step;
	}
	else
	{
		CurrentLaserPoint = TargetLaserPoint;
		SetNextTargetLaserPoint();
	}

	return CurrentLaserPoint;
}

void ACraftingMachine::SetNextTargetLaserPoint()
{
	int Random = FMath::RandRange(0, 3);
	FVector Target = CraftingItemPosition->GetComponentLocation();

	switch (Random)
	{
	case 0:
		Target.X -= CurrentlyCraftingItem->GetBoxExtent().X / 2;
		Target.Y = FMath::RandRange(Target.Y - (CurrentlyCraftingItem->GetBoxExtent().Y / 2), Target.Y + (CurrentlyCraftingItem->GetBoxExtent().Y / 2));
		break;

	case 1:
		Target.X += CurrentlyCraftingItem->GetBoxExtent().X / 2;
		Target.Y = FMath::RandRange(Target.Y - (CurrentlyCraftingItem->GetBoxExtent().Y / 2), Target.Y + (CurrentlyCraftingItem->GetBoxExtent().Y / 2));
		break;

	case 2:
		Target.X = FMath::RandRange(Target.X - (CurrentlyCraftingItem->GetBoxExtent().X / 2), Target.X + (CurrentlyCraftingItem->GetBoxExtent().X / 2));
		Target.Y -= CurrentlyCraftingItem->GetBoxExtent().Y / 2;
		break;

	case 3:
		Target.X = FMath::RandRange(Target.X - (CurrentlyCraftingItem->GetBoxExtent().X / 2), Target.X + (CurrentlyCraftingItem->GetBoxExtent().X / 2));
		Target.Y += CurrentlyCraftingItem->GetBoxExtent().Y / 2;
		break;
	}

	TargetLaserPoint = Target;
}

void ACraftingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CraftingMachineState)
	{
	case ECraftingMachineState::Opening:
		OpeningTick(DeltaTime);
		break;

	case ECraftingMachineState::Closing:
		ClosingTick(DeltaTime);
		break;

	case ECraftingMachineState::Crafting:
		CraftingTick(DeltaTime);
		break;

	case ECraftingMachineState::Finishing:
		FinishingTick(DeltaTime);
		break;
	}
}

void ACraftingMachine::OpeningTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = FMath::Lerp(ClosedAngle, OpenAngle, GetProgress());
		Tray->SetRelativeRotation(Rotation);
	}
	else
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = OpenAngle;
		Tray->SetRelativeRotation(Rotation);
		CraftingMachineState = ECraftingMachineState::Standby;

		HUD->UpdateCraftingMenu();
	}
}

void ACraftingMachine::ClosingTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = FMath::Lerp(OpenAngle, ClosedAngle, GetProgress());
		Rotation.Yaw = -90.0f;
		Rotation.Roll = -90.0f;
		Tray->SetRelativeRotation(Rotation);
	}
	else
	{
		FRotator Rotation = Tray->GetRelativeRotation();
		Rotation.Pitch = ClosedAngle;
		Tray->SetRelativeRotation(Rotation);
		CraftingMachineState = ECraftingMachineState::Closed;
	}
}

void ACraftingMachine::CraftingTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{
		CraftingMaterial->SetScalarParameterValue(TEXT("DissolveAmount"), 100 - (GetProgress() * 100));
		CurrentlyCraftingItem->SetMaterial(CraftingMaterial);

		CraftingLaser->SetVectorParameter(TEXT("BeamEndVec"), GetLaserPosition(DeltaTime));
	}
	else
	{
		CraftingMachineState = ECraftingMachineState::Finishing;
		Timer = PostCraftingPause;
		CraftingLaser->Deactivate();
		CurrentlyCraftingItem->SetMaterial(CurrentlyCraftingItemMaterial);

		GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->UpdateCraftingMenu();

		UAkGameplayStatics::PostEvent(RunningSoundStop, this, int32(0), FOnAkPostEventCallback(), false);
		UAkGameplayStatics::PostEvent(FinishedSound, this, int32(0), FOnAkPostEventCallback(), false);
	}
}

void ACraftingMachine::FinishingTick(float DeltaTime)
{
	Timer -= DeltaTime;

	if (Timer > 0)
	{
	}

	else
	{
		CraftingMachineState = ECraftingMachineState::Standby;

		CurrentlyCraftingItem->Destroy();
		if(!Inventory->AddItemsForRecipe(CurrentlyCrafting))
			UE_LOG(LogTemp, Error, TEXT("Crafting machine could not add recipe item to inventory"));
		CurrentlyCrafting = nullptr;

		GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->UpdateCraftingMenu();
	}
}

void ACraftingMachine::Interact(APlayerCharacter* PlayerCharacter)
{
	Inventory = PlayerCharacter->GetInventoryComponent();
	HUD = PlayerCharacter->GetHUD();

	// start crafting process
	if (CraftingMachineState == ECraftingMachineState::Closed)
	{
		Timer = OpenCloseTime;
		CraftingMachineState = ECraftingMachineState::Opening;

		GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->ShowCraftingMenu();

		UAkGameplayStatics::PostEvent(OpeningSound, this, int32(0), FOnAkPostEventCallback(), false);
	}

	else if (CraftingMachineState == ECraftingMachineState::Standby)
	{
		Timer = OpenCloseTime;
		CraftingMachineState = ECraftingMachineState::Closing;

		GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->HideCraftingMenu();

		UAkGameplayStatics::PostEvent(ClosingSound, this, int32(0), FOnAkPostEventCallback(), false);
	}
}

FString ACraftingMachine::InteractionText()
{
	switch (CraftingMachineState)
	{
	case ECraftingMachineState::Closed: return TEXT("Craft");

	default: return TEXT("");
	}
}

TArray<class URecipeDataAsset*> ACraftingMachine::GetRecipesByType(ECraftingMenuType CraftingMenuType)
{
	TArray<class URecipeDataAsset*> List;

	for (URecipeDataAsset* Recipe : Recipes)
	{
		if (Recipe->CraftingMenuType == CraftingMenuType) List.Add(Recipe);
	}

	return List;
}

float ACraftingMachine::GetProgress()
{
	switch (CraftingMachineState)
	{
	case ECraftingMachineState::Opening:
		return 1 - (Timer / OpenCloseTime);

	case ECraftingMachineState::Closing:
		return 1 - (Timer / OpenCloseTime);

	case ECraftingMachineState::Crafting:
		return 1 - (Timer / CurrentlyCrafting->BuiltTime);

	default: return 1.0f;
	}
}

void ACraftingMachine::Craft(URecipeDataAsset* Recipe)
{
	if (Recipe == nullptr || !Inventory->CanAfford(Recipe) || !Inventory->CanAddItem(Recipe->Item)) return;
	if (Recipe->Item == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Recipe item refence missing"));
		return;
	}
	if (Recipe->Item->ItemClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Recipe Item ItemClass refence missing"));
		return;
	}

	CurrentlyCrafting = Recipe;
	CraftingMachineState = ECraftingMachineState::Crafting;
	if (!Inventory->TakeItemsForRecipe(CurrentlyCrafting))
	{
		UE_LOG(LogTemp, Error, TEXT("Crafting machine could not take recipe items"));
		return;
	}
		


	Timer = CurrentlyCrafting->BuiltTime;

	CurrentlyCraftingItem = GetWorld()->SpawnActor<ASurvivalScifi_Item>(CurrentlyCrafting->Item->ItemClass, CraftingItemPosition->GetComponentLocation(), CraftingItemPosition->GetComponentRotation());
	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(CurrentlyCraftingItem->GetMesh());
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(CurrentlyCraftingItem->GetMesh());

	if (SkeletalMeshComponent != nullptr) SkeletalMeshComponent->SetSimulatePhysics(false);
	if (StaticMeshComponent != nullptr) StaticMeshComponent->SetSimulatePhysics(false);

	CraftingMaterial = UMaterialInstanceDynamic::Create(CraftingMaterialPrefab, this);
	CurrentlyCraftingItemMaterial = CurrentlyCraftingItem->GetMaterial();

	CraftingLaser->Activate();
	SetNextTargetLaserPoint();
	CurrentLaserPoint = CraftingItemPosition->GetComponentLocation();
	CraftingLaser->SetVectorParameter(TEXT("BeamEndVec"), CurrentLaserPoint);


	GetWorld()->GetFirstPlayerController()->GetHUD<ASurvivalScifi_HUD>()->UpdateCraftingMenu();

	UAkGameplayStatics::PostEvent(RunningSound, this, int32(0), FOnAkPostEventCallback(), false);
}

FText ACraftingMachine::CraftingStatusText()
{
	FString Text = TEXT("Crafting ");
	Text += CurrentlyCrafting->Item->Name;
	Text += TEXT(" (");
	int Prog = FMath::Floor(GetProgress() * 100);
	Text += FString::FromInt(Prog);
	Text += TEXT("%)");

	return FText::FromString(Text);
}

