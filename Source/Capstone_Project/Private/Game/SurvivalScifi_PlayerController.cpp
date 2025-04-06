// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalScifi_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PlayerCharacter.h"
#include "UI/SurvivalScifi_HUD.h"
#include "Framework/Application/SlateApplication.h"

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
		Input->BindAction(IA_Jump, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Jump);
		Input->BindAction(IA_InventorySelect, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::InventorySelect);
		Input->BindAction(IA_InventoryAuto, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::InventoryAuto);
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
		if (bUIOnlyMode) SetInputMode(FInputModeUIOnly());
		else
		{
			SetInputMode(FInputModeGameAndUI());
		}
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
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()
		&& !GetHUD<ASurvivalScifi_HUD>()->IsShowingCraftingMenu();
}

bool ASurvivalScifi_PlayerController::AllowMove()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()
		&& !GetHUD<ASurvivalScifi_HUD>()->IsShowingCraftingMenu();
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

void ASurvivalScifi_PlayerController::Jump()
{
	if (PlayerCharacter != nullptr) PlayerCharacter->Jump();
}

void ASurvivalScifi_PlayerController::InventorySelect()
{
	if (!GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()) return;

	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	const FHUDHitBox* HUDHitBox = GetHUD<ASurvivalScifi_HUD>()->GetHitBoxAtCoordinates(MousePosition, false);

	// Get a reference to the singleton instance of the slate application.
	//FSlateApplication& SlateApp = FSlateApplication::Get();

	// Find a "widget tree path" of all widgets under the mouse cursor.
	// This path will contain not only the top-level widget, but all widgets underneath.
	// For example, if the mouse cursor was over a Button with a Text widget inside of it, then the last 
	// widget in the widget path would be the Text widget, and the next to last widget would be the Button widget.
	/*FWidgetPath WidgetsUnderCursor =
		SlateApplication.LocateWindowUnderMouse(SlateApplication.GetCursorPos(), SlateApplication.GetInteractiveTopLevelWindows());

	FString Result = TEXT("");
	if (WidgetsUnderCursor.IsValid())
	{
		Result += TEXT(" Count:") + FString::FromInt(WidgetsUnderCursor.Widgets.Num());

		for (int32 Idx = 0; Idx < WidgetsUnderCursor.Widgets.Num(); ++Idx)
		{
			FArrangedWidget& Widget = WidgetsUnderCursor.Widgets[Idx];

			Result += TEXT(" ") + Widget.Widget->ToString();
		}
	}
	else
		Result += "ERROR";

	// Print out a quick summary of all widgets that were found under the mouse.
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Result); */
}

void ASurvivalScifi_PlayerController::InventoryAuto()
{
	if (!GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()) return;
}
