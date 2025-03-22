// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalScifi_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PlayerCharacter.h"
#include "UI/SurvivalScifi_HUD.h"

void ASurvivalScifi_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacter>(aPawn);

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}

void ASurvivalScifi_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem != nullptr && InputMapping != nullptr)
	{
		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}

	else if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Subsystem Referance"), *GetName());
		return;
	}
	else if (InputMapping == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Mapping Referance"), *GetName());
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (Input != nullptr)
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASurvivalScifi_PlayerController::Move);
		Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ASurvivalScifi_PlayerController::Look);
		Input->BindAction(IA_Inventory, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::ToggleInventory);
		Input->BindAction(IA_Run, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::RunStart);
		Input->BindAction(IA_Run, ETriggerEvent::Completed, this, &ASurvivalScifi_PlayerController::RunEnd);
		Input->BindAction(IA_Interact, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Interact);
		Input->BindAction(IA_Slot1, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot1);
		Input->BindAction(IA_Slot2, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot2);
		Input->BindAction(IA_Slot3, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot3);
		Input->BindAction(IA_Slot4, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot4);
		Input->BindAction(IA_Slot5, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot5);
		Input->BindAction(IA_Use, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::UseItem);
		Input->BindAction(IA_Use, ETriggerEvent::Completed, this, &ASurvivalScifi_PlayerController::UseItemEnd);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void ASurvivalScifi_PlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter != nullptr && AllowMove())
	{
		FRotator CharacterRotation = PlayerCharacter->GetControlRotation();

		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
			Value.Get<FVector2D>().Y);

		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
			Value.Get<FVector2D>().X);
	}
}

void ASurvivalScifi_PlayerController::Look(const FInputActionValue& Value)
{
	if (!AllowLook()) return;

	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(-1 * Value.Get<FVector2D>().Y);
}

void ASurvivalScifi_PlayerController::ToggleInventory(const FInputActionValue& Value)
{
	if (!GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory())
	{
		GetHUD<ASurvivalScifi_HUD>()->ShowInventory();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeGameAndUI());
	}

	else
	{
		GetHUD<ASurvivalScifi_HUD>()->HideInventory();
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());
	}
}

bool ASurvivalScifi_PlayerController::AllowLook()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory();
}

bool ASurvivalScifi_PlayerController::AllowMove()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory();
}

void ASurvivalScifi_PlayerController::RunStart()
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->SetMovementSpeed(true);
	}
}

void ASurvivalScifi_PlayerController::RunEnd()
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->SetMovementSpeed(false);
	}
}

void ASurvivalScifi_PlayerController::Interact()
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->Interact();
	}
}

void ASurvivalScifi_PlayerController::Slot1()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->SelectSlot(1);
}

void ASurvivalScifi_PlayerController::Slot2()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->SelectSlot(2);
}

void ASurvivalScifi_PlayerController::Slot3()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->SelectSlot(3);
}

void ASurvivalScifi_PlayerController::Slot4()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->SelectSlot(4);
}

void ASurvivalScifi_PlayerController::Slot5()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->SelectSlot(5);
}

void ASurvivalScifi_PlayerController::UseItem()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->UseItemRepeating();
}

void ASurvivalScifi_PlayerController::UseItemEnd()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->UseItemEnd();
}
